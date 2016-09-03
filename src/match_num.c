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

void* process_image(void* arg);

typedef struct feature_data_t {
  size_t count;
  struct feature* features;
} FeatureData;

struct thread_data {
  int         thread_id;
  char*       filename;
  FeatureData fdata;
};

void* process_image(void* arg) {
  int n;
  struct thread_data* ctx;
  IplImage*       img;

  ctx = (struct thread_data*)arg;
  img = cvLoadImage(ctx->filename, 1);
  if (!img) fatal_error("Unable to load image from %s", ctx->filename);
  ctx->fdata.count = sift_features(img, &(ctx->fdata.features));
  if (DEBUG)
  fprintf(stderr, "Found %d features in %s...\n", ctx->fdata.count, ctx->filename);
  cvReleaseImage(&img);
  pthread_exit(NULL);
}

int compare_features(FeatureData* f0, FeatureData* f1)
{
  struct kd_node* kd_root;
  double d0, d1;
  struct feature** nbrs;
  int num_matches;
  size_t i; /* Serves as an index into an array, hence, size_t */

  /* Build KD Tree */
  kd_root = kdtree_build(f1->features, f1->count);

  /* Compare feature distances */
  for(i = 0; i < f0->count; ++i) {
    int k;
    struct feature* feat;
    feat = f0->features + i;
    k = kdtree_bbf_knn( kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS );
    if( k == 2 ) {
      d0 = descr_dist_sq( feat, nbrs[0] );
      d1 = descr_dist_sq( feat, nbrs[1] );
      if( d0 < d1 * NN_SQ_DIST_RATIO_THR ) ++num_matches;
    }
    free( nbrs );
  }
  kdtree_release( kd_root );
  return num_matches;
}

int main( int argc, char** argv ) {
  int i;
  pthread_t threads[2];
  struct thread_data td[2];
  pthread_attr_t attr;
  void* status;

  /* Handle filenames */
  if( argc != 3 ) fatal_error( "usage: %s <img1> <img2>", argv[0] );
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

  /* Wait for threads to join */
  for (i=0; i < 2; ++i) {
    int rc;
    rc = pthread_join(threads[i], &status);
    if (rc) fatal_error("Return code from thread pthread_join is %d",rc);
  }

  fprintf( stdout, "%d\n", compare_features(&(td[0].fdata), &(td[1].fdata)));

  /* Release structures */
  for (i=0; i<2; ++i) free(td[i].fdata.features);
  pthread_exit(NULL);

  return 0;
}
