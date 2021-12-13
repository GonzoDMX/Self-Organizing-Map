/*
*	DATASET_OPERATIONS_H_
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	Header file for DATASET_OPERATIONS
*
*/


#ifndef DATASET_OPERATIONS_H_
#define DATASET_OPERATIONS_H_


void normalize_dataset(Dataset *d);

double normalize_elem(double elem, double min_elem, double max_elem);

size_t *get_randomized_order(size_t s);

size_t *get_randomized_list(size_t s);

size_t get_random_sample(size_t s);


#endif // DATASET_OPERATIONS_H_
