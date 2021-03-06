/*
*	TEST_FUNCTIONS_H_
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	Header file for TEST_FUNCTIONS
*
*/

#ifndef TEST_FUNCTIONS_H_
#define TEST_FUNCTIONS_H_


void print_dataset(Dataset *d);

void print_sample_size(Dataset *d);

void print_vector_size(Dataset *d);

void print_min_values(Dataset *d);

void print_max_values(Dataset *d);

void print_avg_values(Dataset *d);

void print_node_map(SOMap *m);

void print_size_t_array(size_t *o, size_t s);

void print_feature_map(SOMap *m);

void print_avg_map(SOMap *m);

void press_enter_to_continue();


#endif
