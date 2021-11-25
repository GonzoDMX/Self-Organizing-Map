/*
*	SOMAP_OPERATIONS_H_
*	Created by: Andrew O'Shei
*	Date: Nov 2, 2021
*	
*	Info:
*	Header file for SOMAP_OPERATIONS
*
*/


#ifndef SOMAP_OPERATIONS_H_
#define SOMAP_OPERATIONS_H_

size_t get_iteration_count(size_t v_size);

size_t *get_best_match_unit(Dataset *d, SOMap *m, size_t index);

double multi_dimen_euclid_distance(const double *v1, const double *v2, size_t v_size);

void update_nodes(Dataset *d, SOMap *m, size_t index, size_t *bmu_pos, size_t t, size_t t_max);

double neighborhood_func(size_t *pos, size_t *bmu_pos, size_t t, size_t t_max);

void set_learning_rate();

void update_learning_rate(size_t t, size_t t_max);

double get_distance(size_t *pos, size_t *bmu_pos);

void reset_feature_map(SOMap *m);

void populate_feature_map(Dataset *d, SOMap *m);

#endif // SOMAP_OPERATIONS_H_
