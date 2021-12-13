/*
*	SOMAP_BUILDER_H_
*	Created by: Andrew O'Shei
*	Date: Nov 2, 2021
*	
*	Info:
*	Header file for SOMAP_BUILDER
*
*/


#ifndef SOMAP_BUILDER_H_
#define SOMAP_BUILDER_H_

typedef struct
{
	// X Position of node in Network
	size_t x;
	// Y Position of Node in Network
	size_t y;
	// Used to draw map at end of training
	int color[3];
	int ett;
	// The nodes weights
	double *weights;
} Node;

typedef struct
{
	// Width of SOMap
	size_t x;
	// Height of SOMap
	size_t y;
	// Size of Node weights vector
	size_t v;
	//  Number of nodes in network
	size_t node_size;
	// Pointer to nodes
	Node **nodes;
} SOMap;

extern Node node;

extern SOMap map;

SOMap build_som(size_t *dimens, size_t v_size, size_t s_size, double *avg);

double *get_random_vector(size_t v_size);

#endif // SOMAP_BUILDER_H_
