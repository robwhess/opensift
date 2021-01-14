/**@file
   Functions and structures for maintaining a k-d tree database of image
   features.
   
   For more information, refer to:
   
   Beis, J. S. and Lowe, D. G.  Shape indexing using approximate
   nearest-neighbor search in high-dimensional spaces.  In <EM>Conference
   on Computer Vision and Pattern Recognition (CVPR)</EM> (2003),
   pp. 1000--1006.
   
   Copyright (C) 2006-2012  Rob Hess <rob@iqengines.com>

   @version 1.1.2-20100521
*/


#ifndef KDTREE_H
#define KDTREE_H

#include <opencv2/core/core_c.h>


/********************************* Structures ********************************/

struct feature;

/** a node in a k-d tree */
struct kd_node
{
  int ki;                      /**< partition key index */
  double kv;                   /**< partition key value */
  int leaf;                    /**< 1 if node is a leaf, 0 otherwise */
  struct feature* features;    /**< features at this node */
  int n;                       /**< number of features */
  struct kd_node* kd_left;     /**< left child */
  struct kd_node* kd_right;    /**< right child */
};


/*************************** Function Prototypes *****************************/

/**
   A function to build a k-d tree database from keypoints in an array.
   
   @param features an array of features; <EM>this function rearranges the order
     of the features in this array, so you should take appropriate measures if
     you are relying on the order of the features (e.g. call this function
     before order is important)</EM>
   @param n the number of features in \a features
   
   @return Returns the root of a kd tree built from \a features.
*/
extern struct kd_node* kdtree_build( struct feature* features, int n );



/**
   Finds an image feature's approximate k nearest neighbors in a kd tree using
   Best Bin First search.
   
   @param kd_root root of an image feature kd tree
   @param feat image feature for whose neighbors to search
   @param k number of neighbors to find
   @param nbrs pointer to an array in which to store pointers to neighbors
     in order of increasing descriptor distance; memory for this array is
     allocated by this function and must be freed by the caller using
     free(*nbrs)
   @param max_nn_chks search is cut off after examining this many tree entries
   
   @return Returns the number of neighbors found and stored in \a nbrs, or
     -1 on error.
*/
extern int kdtree_bbf_knn( struct kd_node* kd_root, struct feature* feat,
			   int k, struct feature*** nbrs, int max_nn_chks );


/**
   Finds an image feature's approximate k nearest neighbors within a specified
   spatial region in a kd tree using Best Bin First search.
   
   @param kd_root root of an image feature kd tree
   @param feat image feature for whose neighbors to search
   @param k number of neighbors to find
   @param nbrs pointer to an array in which to store pointers to neighbors
     in order of increasing descriptor distance; memory for this array is
     allocated by this function and must be freed by the caller using
     free(*nbrs)
   @param max_nn_chks search is cut off after examining this many tree entries
   @param rect rectangular region in which to search for neighbors
   @param model if true, spatial search is based on kdtree features' model
     locations; otherwise it is based on their image locations
   
   @return Returns the number of neighbors found and stored in \a nbrs
     (in case \a k neighbors could not be found before examining
     \a max_nn_checks keypoint entries).
*/
extern int kdtree_bbf_spatial_knn( struct kd_node* kd_root,
				   struct feature* feat, int k,
				   struct feature*** nbrs, int max_nn_chks,
				   CvRect rect, int model );


/**
   De-allocates memory held by a kd tree

   @param kd_root pointer to the root of a kd tree
*/
extern void kdtree_release( struct kd_node* kd_root );


#endif
