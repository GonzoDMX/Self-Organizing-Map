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
#include "somap_builder.h"


SOMap build_som(size_t v_size)
{
	SOMap m;
	m.v = v_size;
	get_map_dimensions(&m);
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


void get_map_dimensions(SOMap *m)
{
	size_t x, y, n;
	while(1)
	{
		printf("\nWhat is the X-size (width) of your Self-Organizing Map?\n");
		scanf("%zu", &x);
		printf("What is the Y-size (height) of your Self-Organizing Map?\n");
		scanf("%zu", &y);
		printf("\n\nX: %ld | Y: %ld\n", x, y);
		if (x > 1 && y > 1)
		{
			getchar();
			n = x * y;
			printf("Initializing a (%ld, %ld) Self-Organizing Map with %ld nodes.\n", x, y, n);
			m->x = x;
			m->y = y;
			m->node_size = n;
			break;
		}
		printf("\nERROR: X-Size and Y-Size must be whole numbers greater than 1.\n");
	}
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
