/*
  Detects SIFT features in two images and finds matches between them.

  Copyright (C) 2006-2012  Rob Hess <rob@iqengines.com>

  @version 1.1.2-20100521
*/

#include "sift.h"
#include "imgfeatures.h"
#include "kdtree.h"
#include "utils.h"
#include "xform.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <stdio.h>
#include <pthread.h>

#define DEBUG 1

/* the maximum number of keypoint NN candidates to check during BBF search */
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49

struct thread_data {
  int             thread_id;
  char*           filename;
  int             num_features;
  struct feature* features;
};

void* process_image(void* arg) {
  int n;
  struct thread_data* ctx;
  IplImage*       img;

  ctx = (struct thread_data*)arg;
  img = cvLoadImage(ctx->filename, 1);
  if (!img) fatal_error("Unable to load image from %s", ctx->filename);
  ctx->num_features = sift_features(img, &(ctx->features));
  if (DEBUG)
  fprintf(stderr, "Found %d features in %s...\n", ctx->num_features, ctx->filename);
  cvReleaseImage(&img);
  pthread_exit(NULL);
}

int main( int argc, char** argv ) {
  struct feature** nbrs;
  struct kd_node* kd_root;
  CvPoint pt1, pt2;
  double d0, d1;
  int i, num_matches = 0;
  pthread_t threads[2];
  struct thread_data td[2];
  pthread_attr_t attr;
  void* status;
  


  /* Handle filenames */
  if( argc != 3 )
    fatal_error( "usage: %s <img1> <img2>", argv[0] );

  td[0].filename=argv[1];
  td[1].filename=argv[2];


  /* Launch processing threads */

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (i=0; i < 2; ++i) { 
    int rc;
    rc = pthread_create(&threads[i], &attr, process_image, (void*)&td[i]);
    if (rc) fatal_error("Unable to create processing thread (err %d).",rc);
  }

  pthread_attr_destroy(&attr);

  /* Wait for threads */

  for (i=0; i < 2; ++i) {
    int rc;
    rc = pthread_join(threads[i], &status);
    if (rc) fatal_error("Return code from thread pthread_join is %d",rc);
  }

  kd_root = kdtree_build(td[1].features, td[1].num_features);

  for(i = 0; i < td[0].num_features; ++i) {
    int k;
    struct feature* feat;
    feat = td[0].features + i;
    k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
    if( k == 2 ) {
      d0 = descr_dist_sq( feat, nbrs[0] );
      d1 = descr_dist_sq( feat, nbrs[1] );
      if( d0 < d1 * NN_SQ_DIST_RATIO_THR ) ++num_matches;
    }
    free( nbrs );
  }

  fprintf( stdout, "%d\n", num_matches);

  kdtree_release( kd_root );
  /* Release structures */
  for (i=0; i<2; ++i) free(td[i].features);
  pthread_exit(NULL);
  return 0;
}
