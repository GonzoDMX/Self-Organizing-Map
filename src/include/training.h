/*
*	TRAIN_FUNCTIONS_H_
*	Created by: Andrew O'Shei
*	Date: Dec 13, 2021
*	
*	Info:
*	Header file for TRAIN_FUNCTIONS
*
*/

#ifndef TRAIN_FUNCTIONS_H_
#define TRAIN_FUNCTIONS_H_

// Set the map radius, used for calculating the neighborhood size
double set_map_radius(size_t x, size_t y);

// Set the time constant for calculating neighborhood size
double set_time_constant(size_t iterations, double map_radius);

// Calculates and then returns the learning rate
double set_learning_rate(double l, double delay, size_t t, size_t t_max);

// Set the neighborhood size for the current iteration
double set_neighborhood_size(double map_radius, int t, double time_constant);

// Find the best match unit for the given input vector
Node *get_best_match_unit(double *target, SOMap *m);

// Used to grab random BMU
int get_random_val();

// Given two n-dimensional vectors, find the euclidean distance between them
double multi_dimen_euclid_distance(const double *v_one, const double *v_two, size_t n_dimens);

// Calculate the squared distance between two coordinates
double get_squared_distance(size_t x_a, size_t y_a, size_t x_b, size_t y_b);

// Calculate the influence rate
double get_influence_rate(double distanceSq, double neighborSq);

// Traverse the SOMap node detwork and update activated nodes
void update_nodes(double *target, Node *bmu, double learning_rate, double neighborhood, SOMap *m);

// Update the node weights
void update_node_weights(double *target, Node *n, size_t v_size, double l_rate, double influence);

#endif
