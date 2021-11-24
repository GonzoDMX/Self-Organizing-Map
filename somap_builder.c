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
#include "somap_builder.h"


SOMap build_som(size_t v_size, size_t s_size)
{
	SOMap m;
	// Set Vector Size
	m.v = v_size;
	
	// Get dimensions of SOMap
	set_map_dimensions(&m, s_size);
	
	srand(time(NULL));
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
			n.color = 0;
			m.nodes[i][j] = n;
		}
	}
	return m;
}


// Set SOMap Dimensions automatically based on number of nodes
void set_map_dimensions(SOMap *m, size_t sample_size)
{
	size_t x, y, n;
	n = 5 * sqrt(sample_size);
	x = sqrt(n);
	while(1)
	{
		if(n % x == 0)
		{
			y = n / x;
			if(y > 4 || x == y)
			{
				break;
			}
			x = sqrt(--n);
		}
		else
		{
			x++;
		}
	}
	m->x = x;
	m->y = y;
	m->node_size = n;
	printf("Number of Nodes: %ld\n", n);
	printf("x: %ld | y: %ld\n", x, y);
}


// Used for building random vectors
double *get_random_vector(size_t v_size)
{
	double *v;
	v = (double*)malloc(sizeof(double) * v_size);
	for (int i = 0; i < v_size; i++)
	{
		v[i] = (double)rand()/RAND_MAX;
	}
	return v;
}
