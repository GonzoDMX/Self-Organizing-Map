/*
*	SOMAP_OPERATIONS
*	Created by: Andrew O'Shei
*	Date: Nov 2, 2021
*	
*	Info:
*	Functions for manipulating the SOM Node Network
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "dataset_builder.h"
#include "somap_builder.h"
#include "somap_operations.h"


size_t get_iteration_count()
{
	size_t x;
	while(1)
	{
		printf("\nIn how many iterations would you like to train the SOM?\n");
		scanf("%zu", &x);
		
		if (x > 0)
		{
			getchar();
			printf("Preparing to train the SOM for %ld iterations.\n", x);
			break;
		}
		printf("\nERROR: Number of iterations must be a whole number greater than 0.\n");
	}
	return x;
}


size_t *get_best_match_unit(Dataset *d, SOMap *m, size_t index)
{
	double dist=DBL_MAX, tmp;
	size_t *pos = (size_t*)malloc(sizeof(size_t) * 2);
	for (size_t i = 0; i < m->y; i++)
	{
		for (size_t j = 0; j < m->x; j++)
		{
			Node node = m->nodes[i][j];
			tmp = multi_dimen_euclid_distance(d->data[index], node.weights, m->v);
			if (tmp < dist)
			{
				dist = tmp;
				pos[0] = j;
				pos[1] = i;
			}
		}
	}
	return pos;
}


double multi_dimen_euclid_distance(const double *v1, const double *v2, size_t v_size)
{
	double distance=0, tmp, result;	
	for (size_t i = 0; i < v_size; i++)
	{
		tmp = v1[i] - v2[i];
		tmp = pow(tmp, 2);
		distance += tmp;
	}
	// Return the square root of the squared Euclidean distance
	return sqrt(distance);
}



// Update vector algo
// Weight[v] + Neighbourhood Function * Learning Restraint * (Sample[v] - Weight[v])


// Args; Dataset, Node Map, Index of Sample, Best Match Unit Position, Iteration, Total Iterations
void update_nodes(Dataset *d, SOMap *m, size_t index, size_t *bmu_pos, size_t t, size_t t_max)
{
	for (int i = 0; i < m->y; i++)
	{
		for (int j = 0; j < m->x; j++)
		{
			for (int k = 0; k < d->vector_size; k++)
			{
				// Update Algorithm
				size_t pos[2] = { j, i };
				double v = d->data[index][k];
				double w = m->nodes[i][j].weights[k];
				double n_func = neighborhood_func(pos, bmu_pos, (t+1), t_max);
				double l_rate = learning_rate((t+1), t_max);
				m->nodes[i][j].weights[k] = w + l_rate * n_func * (v - w);
			}
		}
	}	
}

// Function for calculating neighborhood threshold
double neighborhood_func(size_t *pos, size_t *bmu_pos, size_t t, size_t t_max)
{
	double dist = pow(get_distance(pos, bmu_pos), 2);
	double rate = pow(learning_rate(t, t_max), 2) * 2 * t;
	double result = exp(-dist/rate);
	return result;
}

// Function for calculating learning rate
double learning_rate(size_t t, size_t t_max)
{
	double t_tmp = (double)t / t_max;
	t_tmp = exp(-t_tmp);
	return t_tmp;
}

double get_distance(size_t *pos, size_t *bmu_pos)
{
	double x_val, y_val;
	x_val = pow((double)(pos[0] - bmu_pos[0]), 2);
	y_val = pow((double)(pos[1] - bmu_pos[1]), 2);
	return sqrt(x_val + y_val);
}


void reset_feature_map(SOMap *m)
{
	for (size_t i = 0; i < m->y; i++)
	{
		for (size_t j = 0; j < m->x; j++)
		{
			m->nodes[i][j].color = 0;
		}
	}
}

void populate_feature_map(Dataset *d, SOMap *m)
{
	for (size_t i = 0; i < d->sample_size; i++)
	{
		size_t *pos;
		pos = get_best_match_unit(d, m, i);
		m->nodes[pos[1]][pos[0]].color += 1;
	}
}
