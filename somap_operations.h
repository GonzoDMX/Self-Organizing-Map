/*
*
*	Header file for SOM Operations module
*
*/


#ifndef SOMAP_OPERATIONS_H_
#define SOMAP_OPERATIONS_H_


size_t get_iteration_count();

size_t *get_best_match_unit(Dataset *d, SOMap *m, size_t index);

double multi_dimen_euclid_distance(const double *v1, const double *v2, size_t v_size);

void update_nodes(Dataset *d, SOMap *m, size_t index, size_t *bmu_pos, size_t t, size_t t_max);

double neighborhood_func(size_t *pos, size_t *bmu_pos, size_t t, size_t t_max);

double learning_rate(size_t t, size_t t_max);

double get_distance(size_t *pos, size_t *bmu_pos);

#endif // SOMAP_OPERATIONS_H_
