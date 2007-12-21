/*
  This file is part of p4est.
  p4est is a C library to manage a parallel collection of quadtrees and/or
  octrees.

  Copyright (C) 2007 Carsten Burstedde, Lucas Wilcox.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __P4EST_ALGORITHMS_H__
#define __P4EST_ALGORITHMS_H__

#include <p4est.h>

/** Compare two quadrants in their Morton ordering.
 * \return Returns < 0 if \a v1 < \a v2,
 *                   0 if \a v1 == \a v2,
 *                 > 0 if \a v1 > \a v2
 */
int                 p4est_quadrant_compare (const void *v1, const void *v2);

/** Test if two quadrants have equal Morton indices.
 * \return 1 if \a v1 describes the same quadrant as \a v2.
 */
int                 p4est_quadrant_is_equal (const void *v1, const void *v2);

/** Computes a hash value for a quadrant.
 */
int                 p4est_quadrant_hash (const void *v);

/** Compute the position of this child within its siblings.
 * \return Returns its child id in 0..3
 */
int8_t              p4est_quadrant_child_id (const p4est_quadrant_t * q);

/** Test if a quadrant has valid Morton indices.
 * \param [in] q Quadrant to be tested.
 * \return Returns 1 if \a q is valid.
 */
int                 p4est_quadrant_is_valid (const p4est_quadrant_t * q);

/** Test if two quadrants are siblings.
 * \param [in] q1 First quadrant to be tested.
 * \param [in] q2 Second quadrant to be tested.
 * \return 1 if \a q1 is unequal to and a sibling of \a q2.
 */
int                 p4est_quadrant_is_sibling (const p4est_quadrant_t * q1,
                                               const p4est_quadrant_t * q2);

/** Test if two quadrants are siblings.
 * Descriptive, slower version of \a p4est_quadrant_is_sibling.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_sibling_D (const p4est_quadrant_t * q1,
                                                 const p4est_quadrant_t * q2);

/** Test if four quadrants are siblings in Morton ordering.
 */
int                 p4est_quadrant_is_family (const p4est_quadrant_t * q0,
                                              const p4est_quadrant_t * q1,
                                              const p4est_quadrant_t * q2,
                                              const p4est_quadrant_t * q3);

/** Test if a quadrant it the parent of another quadrant.
 * \param [in] q Quadrant to be tested.
 * \param [in] r Possible child quadrant.
 * \return 1 if \a q is the parent of \a r.
 */
int                 p4est_quadrant_is_parent (const p4est_quadrant_t * q,
                                              const p4est_quadrant_t * r);

/** Test if a quadrant it the parent of another quadrant.
 * Descriptive, slower version of \a p4est_quadrant_is_parent.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_parent_D (const p4est_quadrant_t * q,
                                                const p4est_quadrant_t * r);

/** Test if a quadrant is an ancestor of another quadrant.
 * \param [in] q Quadrant to be tested.
 * \param [in] r Descendent quadrant.
 * \return 1 if \a q is unequal to and an ancestor of \a r.
 */
int                 p4est_quadrant_is_ancestor (const p4est_quadrant_t * q,
                                                const p4est_quadrant_t * r);

/** Test if a quadrant is an ancestor of another quadrant.
 * Descriptive, slower version of \a p4est_quadrant_is_ancestor.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_ancestor_D (const p4est_quadrant_t * q,
                                                  const p4est_quadrant_t * r);

/** Test if two quadrants follow each other in the tree with no holes.
 * \param [in] q A quadrant
 * \param [in] r Another quadrant
 * \return 1 if \a q is immediately before \a r in the tree.
 * \note for every \a q there are between 0 and P4EST_MAXLEVEL+1 possible nexts.
 */
int                 p4est_quadrant_is_next (const p4est_quadrant_t * q,
                                            const p4est_quadrant_t * r);

/** Test if two quadrants follow each other in the tree with no holes.
 * Descriptive, slower version of \a p4est_quadrant_is_next.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_next_D (const p4est_quadrant_t * q,
                                              const p4est_quadrant_t * r);

/** Compute the parent of a quadrant.
 * \param [in]  q Input quadrant.
 * \param [in,out] r Existing quadrant whose Morton index will be filled
 *                   with the Morton index of the parent of \a q.
 *                   Its user_data will be untouched.
 * \note \a q may point to the same quadrant as \a r.
         The user_data of \a r is never modified.
 */
void                p4est_quadrant_parent (const p4est_quadrant_t * q,
                                           p4est_quadrant_t * r);

/** Compute a specific sibling of a quadrant.
 * \param [in]     q  Input quadrant.
 * \param [in,out] r  Existing quadrant whose Morton index will be filled
 *                    with the coordinates of sibling no. sibling_id of q.
 * \param [in]     sibling_id The id of the sibling computed, 0..3.
 */
void                p4est_quadrant_sibling (const p4est_quadrant_t * q,
                                            p4est_quadrant_t * r,
                                            int8_t sibling_id);

/** Compute the 4 children of a quadrant.
 * \param [in]     q  Input quadrant.
 * \param [in,out] c0 First computed child.
 *                    \a q may point to the same quadrant as \a c0.
 * \note The user_data of \a c0, c1, c2, c3 is never modified.
 */
void                p4est_quadrant_children (const p4est_quadrant_t * q,
                                             p4est_quadrant_t * c0,
                                             p4est_quadrant_t * c1,
                                             p4est_quadrant_t * c2,
                                             p4est_quadrant_t * c3);

/** Compute the first descendent of a quadrant on a given level.
 * \param [in]  q      Input quadrant.
 * \param [out] fd     First descendent of \a q on level \a level.
 * \param [in]  level  Level must be greater equal than q's level.
 */
void                p4est_quadrant_first_descendent (const p4est_quadrant_t *
                                                     q, p4est_quadrant_t * fd,
                                                     int8_t level);

/** Compute the last descendent of a quadrant on a given level.
 * \param [in]  q      Input quadrant.
 * \param [out] ld     Last descendent of \a q on level \a level.
 * \param [in]  level  Level must be greater equal than q's level.
 */
void                p4est_quadrant_last_descendent (const p4est_quadrant_t *
                                                    q, p4est_quadrant_t * ld,
                                                    int8_t level);

/** Computes the nearest common ancestor of two quadrants.
 * \param [in]     q1 First input quadrant.
 * \param [in]     q2 Second input quadrant.
 * \param [in,out] r Existing quadrant whose Morton index will be filled.
 *                   Its user_data will be untouched.
 * \note \a q1, \a q2, \a r may point to the same quadrant.
 *       The user_data of \a r is never modified.
 */
void                p4est_nearest_common_ancestor (const p4est_quadrant_t *
                                                   q1,
                                                   const p4est_quadrant_t *
                                                   q2, p4est_quadrant_t * r);

/** Computes the nearest common ancestor of two quadrants.
 * Descriptive, slower version of \a p4est_nearest_common_ancestor.
 * For debugging and educationial purposes only.
 */
void                p4est_nearest_common_ancestor_D (const p4est_quadrant_t *
                                                     q1,
                                                     const p4est_quadrant_t *
                                                     q2,
                                                     p4est_quadrant_t * r);

/** Computes the linear position of a quadrant in a uniform grid.
 * \param [in] quadrant  Quadrant whose id will be computed.
 * \return Returns the linear position of this quadrant on a grid.
 * \note This is the inverse operation of p4est_quadrant_set_morton.
 *       The user_data of \a quadrant is never modified.
 */
int64_t             p4est_quadrant_linear_id (const p4est_quadrant_t *
                                              quadrant, int8_t level);

/** Set quadrant Morton indices based on linear position in uniform grid.
 * \param [in,out] quadrant  Quadrant whose Morton indices will be set.
 * \param [in]     id        The linear position of this quadrant on a grid.
 * \note This is the inverse operation of p4est_quadrant_linear_id.
 *       The user_data of \a quadrant is never modified.
 */
void                p4est_quadrant_set_morton (p4est_quadrant_t * quadrant,
                                               int8_t level, int64_t id);

/** Alloc and initialize the user data of a valid quadrant.
 * \param [in]  which_tree 0-based index of this quadrant's tree.
 * \param [in,out]  quad       The quadrant to be initialized.
 * \param [in]  init_fn    User-supplied callback function to init data.
 */
void                p4est_quadrant_init_data (p4est_t * p4est,
                                              int32_t which_tree,
                                              p4est_quadrant_t * quad,
                                              p4est_init_t init_fn);

/** Free the user data of a valid quadrant.
 * \param [in,out]  quad The quadrant whose data shall be freed.
 */
void                p4est_quadrant_free_data (p4est_t * p4est,
                                              p4est_quadrant_t * quad);

void                p4est_quadrant_print (const p4est_quadrant_t * q,
                                          int identifier, FILE * nout);

/** Test if a tree is sorted in Morton ordering.
 * \return Returns 1 if sorted, 0 otherwise.
 * \note Duplicate quadrants are not allowed.
 */
int                 p4est_tree_is_sorted (p4est_tree_t * tree);

/** Test if a tree is sorted in Morton ordering and linear.
 * \return Returns 1 if linear, 0 otherwise.
 * \note Linear means that the tree has no overlaps.
 */
int                 p4est_tree_is_linear (p4est_tree_t * tree);

/** Test if a tree is sorted in Morton ordering and complete.
 * \return Returns 1 if complete, 0 otherwise.
 * \note Complete means that the tree has no holes and no overlaps.
 */
int                 p4est_tree_is_complete (p4est_tree_t * tree);

/** Print the quadrants in a tree.
 * Prints one line per quadrant with x, y, level and a string.
 * The string denotes the relation to the previous quadrant and can be:
 *   Fn  for the first quadrant in the tree with child id n
 *   I   for identical quadrants
 *   R   for a quadrant that with smaller Morton index
 *   Cn  for child id n
 *   Sn  for sibling with child id n
 *   D   for a descendent
 *   Nn   for a next quadrant in the tree with no holes in between and child id n
 *   qn  for a general quadrant whose child id is n
 * \param [in] tree        Any (possibly incomplete, unsorted) tree to be printed.
 * \param [in] identifier  If >= 0, each line is prefixed by "[identifier] "
 * \param [in] nout        Stream to print to. May be NULL, then nothing happens.
 */
void                p4est_tree_print (p4est_tree_t * tree, int identifier,
                                      FILE * nout);

/** Checks a p4est for validity.
 * A valid p4est has the following properties:
 *    the quadrant counters are consistent
 *    all trees are complete
 *    all non-local trees are empty
 * \param [in] p4est  The p4est to be tested.
 * \return Returns 1 if valid, 0 otherwise.
 */
int                 p4est_is_valid (p4est_t * p4est);

/** Compute the overlap of a number of insulation layers with a tree.
 * Every quadrant out of the insulation layer of the quadrants in \a in
 * except the quadrant itself is checked for overlap of quadrants
 * from \a tree that are smaller by at least two levels and thus can cause
 * a split. Those elements from tree that overlap are put into \a out.
 * \param [in] tree     A sorted complete linear tree to be checked against.
 * \param [in] in       A sorted linear list of quadrants.
 * \param [in,out] out  A sorted subset of \a in. Zero size on input.
 */
void                p4est_tree_compute_overlap (p4est_tree_t * tree,
                                                p4est_array_t * in,
                                                p4est_array_t * out);

/** Constructs a minimal linear octree between two octants.
 *
 * This is alogorithm 2 from H. Sundar, R.S. Sampath and G. Biros
 * with the additional improvements that we do not require sorting
 * and the runtime is O(N).
 *
 * \pre \a q1 < \a q2 in the Morton ordering.
 *
 * \param [in]  p4est used for the memory pools and quadrant init.
 * \param [in]  q1         First input quadrant.  The user data will not change.
 * \param [in]  include_q1 Flag is set to true if q1 is included.
 * \param [in]  q2         First input quadrant.  The user data will not change.
 * \param [in]  include_q2 Flag is set to true if q2 is included.
 * \param [out] tree       Initialized tree with zero elements.
 * \param [in]  which_tree The 0-based index of \a tree which is needed for
 *                         the \c p4est_quadrant_init_data routine.
 * \param [in]  init_fn    Callback function to initialize the user_data
 *                         which is already allocated automatically.
 */
void                p4est_complete_region (p4est_t * p4est,
                                           const p4est_quadrant_t * q1,
                                           int include_q1,
                                           const p4est_quadrant_t * q2,
                                           int include_q2,
                                           p4est_tree_t * tree,
                                           int32_t which_tree,
                                           p4est_init_t init_fn);

/** Completes a sorted subtree.
 * \param [in]     p4est used for the memory pools and quadrant init.
 * \param [in,out] tree       On input, a sorted tree. On output,
 *                            a sorted complete linear tree.
 * \param [in]     which_tree The 0-based index of \a tree which is needed for
 *                            the \c p4est_quadrant_init_data routine.
 * \param [in]     init_fn    Callback function to initialize the user_data
 *                            which is already allocated automatically.
 */
void                p4est_complete_subtree (p4est_t * p4est,
                                            p4est_tree_t * tree,
                                            int32_t which_tree,
                                            p4est_init_t init_fn);

/** Balances a sorted subtree.
 * \param [in]     p4est used for the memory pools and quadrant init.
 * \param [in,out] tree       On input, a sorted tree. On output,
 *                            a sorted complete linear balanced tree.
 * \param [in]     which_tree The 0-based index of \a tree which is needed for
 *                            the \c p4est_quadrant_init_data routine.
 * \param [in]     init_fn    Callback function to initialize the user_data
 *                            which is already allocated automatically.
 */
void                p4est_balance_subtree (p4est_t * p4est,
                                           p4est_tree_t * tree,
                                           int32_t which_tree,
                                           p4est_init_t init_fn);

/** Remove overlaps from a sorted list of quadrants.
 *
 * This is alogorithm 8 from H. Sundar, R.S. Sampath and G. Biros
 * with the additional improvement that it works in-place.
 *
 * \param [in]     p4est used for the memory pool and quadrant free.
 * \param [in,out] tree   A sorted tree to be linearized in-place.
 */
void                p4est_linearize_subtree (p4est_t * p4est,
                                             p4est_tree_t * tree);

#endif /* !__P4EST_ALGORITHMS_H__ */