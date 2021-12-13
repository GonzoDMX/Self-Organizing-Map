/*
*	TRAINING
*	Created by: Andrew O'Shei
*	Date: Dec 13, 2021
*	
*	Info:
*	Functions used to train the network
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "include/dataset_builder.h"
#include "include/somap_builder.h"
#include "include/training.h"


// Set the map radius, used for calculating the neighborhood size
double set_map_radius(size_t x, size_t y)
{
	return ((double)fmax(x, y)/2.0);
}



// Set the time constant for calculating neighborhood size
double set_time_constant(size_t iterations, double map_radius)
{
	return ((double)iterations/log(map_radius));
}



// Function for calculating learning rate
double set_learning_rate(double l, double delay, size_t t, size_t t_max)
{
	double l_rate;
	if(t == 0)
	{
		l_rate = l;
	}
	else
	{
		//l_rate =  l / (1 + t / (t_max / 2));
		//l_rate = l * exp(-(double)t/t_max);
		
		// Taken from Tensorflow Docs
		l_rate = l * (1 / (1 + delay * t));
		printf("Learning rate: %lf\n", l_rate);
	}
	return l_rate;
}



// Set the neighborhood size for the current iteration
double set_neighborhood_size(double map_radius, int t, double time_constant)
{
	return (map_radius * exp(-(double)t/time_constant));
}



// Find the best match unit at index
Node *get_best_match_unit(double *target, SOMap *m)
{
	double dist=DBL_MAX, tmp;
	Node *bmu_node = NULL;
	for (size_t i = 0; i < m->y; i++)
	{
		for (size_t j = 0; j < m->x; j++)
		{
			//double *prob = get_random_vector(1);
			double *weights;
			//if(prob[0] > 0.5)
			//{
				weights = m->nodes[i][j].weights;
				tmp = multi_dimen_euclid_distance(target, weights, m->v);
				if (tmp < dist)
				{
					dist = tmp;
					bmu_node = &m->nodes[i][j];
				}
			//}
		}
	}
	return bmu_node;
}



// Given two n-dimensional vectors, find the euclidean distance between them
double multi_dimen_euclid_distance(const double *v_one, const double *v_two, size_t n_dimens)
{
	double distance=0;	
	for (int i = 0; i < n_dimens; i++)
	{
		distance += (v_one[i] - v_two[i]) * (v_one[i] - v_two[i]);
	}
	// Return the square root of the squared Euclidean distance
	return sqrt(distance);
}



// Calculate the squared distance between two coordinates
double get_squared_distance(size_t x_a, size_t y_a, size_t x_b, size_t y_b)
{
	return (double)((x_a - x_b) * (x_a - x_b) + (y_a - y_b) * (y_a - y_b));
}



// Calculate the influence rate
double get_influence_rate(double distanceSq, double neighborSq)
{
	return exp(-(distanceSq) / (2 * neighborSq));
}



// Traverse the SOMap node detwork and update activated nodes
void update_nodes(double *target, Node *bmu, double learning_rate, double neighborhood, SOMap *m)
{
	double neighborSq = pow(neighborhood, 2);
	for(int i = 0; i < m->y; i++)
	{
		for(int j = 0; j < m->x; j++)
		{
			// Calculate distance between node and BMU
			double distSq = get_squared_distance(m->nodes[i][j].x, m->nodes[i][j].y, bmu->x, bmu->y);
			// If the node is in the neighborhood update its weights
			if(distSq < neighborSq)
			{
				// Calculate influence based on nodes distance and neighborhood size
				double influence = get_influence_rate(distSq, neighborSq);
				
				// Update the node's weights
				update_node_weights(target, &m->nodes[i][j], m->v, learning_rate, influence);
			}
		}
	}
}



// Update the node weights
void update_node_weights(double *target, Node *n, size_t v_size, double l_rate, double influence)
{
	for (int i = 0; i < v_size; i++)
	{
		n->weights[i] += l_rate * influence * (target[i] - n->weights[i]);
	}
}
