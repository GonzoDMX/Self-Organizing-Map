/*
*
*	Header file for test_functions.c
*	A collection of functions for printing data structures for SOM
*
*/

#ifndef TEST_FUNCTIONS_H_
#define TEST_FUNCTIONS_H_



void print_dataset(Dataset *d);

void print_sample_size(Dataset *d);

void print_vector_size(Dataset *d);

void print_min_values(Dataset *d);

void print_max_values(Dataset *d);

void print_node_map(SOMap *m);

void print_size_t_array(size_t *o, size_t s);

void press_enter_to_continue();

#endif
