/*
*	SOMAP_BUILDER
*	Created by: Andrew O'Shei
*	Date: Nov 2, 2021
*	
*	Info:
*	Functions for building an SOM Node Network
*
*/



#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include "include/somap_builder.h"

// Build the Self Organizing Map Node Network
SOMap build_som(size_t *dimens, size_t v_size, size_t s_size, double *avg)
{
	SOMap m;
	// Set Vector Size
	m.v = v_size;
	
	// Set dimensions of SOMap
	m.x = dimens[0];
	m.y = dimens[1];
	m.node_size = dimens[0] * dimens[1];
	
	//srand(time(NULL));
	m.nodes = (Node**)malloc(sizeof(Node) * m.y);
	for (int i = 0; i < m.y; i++)
	{
		m.nodes[i] = (Node*)malloc(sizeof(Node) * m.x);
		for (int j = 0; j < m.x; j++)
		{
			// Initialize a Node
			Node n;
			n.weights = get_random_vector(m.v);
			n.x = j;
			n.y = i;
			n.color[0] = 0;
			n.color[1] = 0;
			n.color[2] = 0;
			m.nodes[i][j] = n;
		}
	}
	return m;
}


// Used for building random vectors
double *get_random_vector(size_t v_size)
{
	double *v;
	v = (double*)malloc(sizeof(double) * v_size);
	for (int i = 0; i < v_size; i++)
	{
		v[i] = (double)rand()/(RAND_MAX);
	}
	return v;
}
