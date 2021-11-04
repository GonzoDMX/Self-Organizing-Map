/*
*
*	Header file for dataset_operations.c
*	Operations for manipulating the dataset
*
*/


#ifndef DATASET_OPERATIONS_H_
#define DATASET_OPERATIONS_H_


void normalize_dataset(Dataset *d);

double normalize_elem(double elem, double min_elem, double max_elem);

size_t *get_randomized_order(size_t s);

size_t get_random_sample(size_t s);


#endif // DATASET_OPERATIONS_H_
