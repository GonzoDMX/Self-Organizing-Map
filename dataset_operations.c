/*
*	DATASET_OPERATIONS
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	A series of functions for manipulating the Dataset Struct
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dataset_builder.h"
#include "dataset_operations.h"


// Scale the dataset to values ranging from 0.0 to 1.0
void normalize_dataset(Dataset *d)
{
	double tmp;
	for (int i = 0; i < d->sample_size; i++)
	{
		for (int j = 0; j < d->vector_size; j++)
		{
			tmp = normalize_elem(d->vector[i].data[j], d->min_values[j], d->max_values[j]);
			d->vector[i].data[j] = tmp;
		}
	}	
}

// Normalize elem to a range from 0.0 to 1.0
double normalize_elem(double elem, double min_elem, double max_elem)
{
	return (elem - min_elem) / (max_elem - min_elem);
}


size_t *get_randomized_order(size_t s)
{
	size_t *order, *r_order, tmp;
	// Seed the random function
	srand(time(NULL));
	// Allocate mem for our two arrays
	order = (size_t*)malloc(sizeof(size_t) * s);
	r_order = (size_t*)malloc(sizeof(size_t) * s);
	// Generate an ordered array and a random array
	for (size_t i = 0; i < s; i++)
	{
		order[i] = i;
		r_order[i] = get_random_sample(s);
	}
	for (size_t i = 0; i < s; i++)
	{
		tmp = order[i];
		order[i] = order[r_order[i]];
		order[r_order[i]] = tmp;
	}
	free(r_order);
	return order;
}

// Used for choosing a random sample
size_t get_random_sample(size_t s)
{
	// return (rand() % dataset.sample_size);
	return (rand() % s);
}
