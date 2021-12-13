/*
*	REQUEST_PARAMS_H_
*	Created by: Andrew O'Shei
*	Date: Dec 13, 2021
*	
*	Info:
*	Header file for REQUEST_PARAMS
*
*/

#ifndef REQUEST_PARAMS_H_
#define REQUEST_PARAMS_H_

// Function for setting the SOMap dimensions
size_t *get_map_dimensions(size_t sample_size);

// Set SOMap Dimensions automatically based on number of nodes
size_t *auto_dimensions(size_t sample_size);

// Request the nmber of training iterations
size_t get_iteration_count(size_t v_size);

// Request the starting learning rate
double get_learning_rate();

// Request the starting learning rate delay
double get_learning_delay();

#endif
