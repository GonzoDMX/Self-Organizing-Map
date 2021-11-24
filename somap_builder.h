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
	size_t x;
	size_t y;
	size_t color;
	double *weights;
} Node;

typedef struct
{
	size_t x;
	size_t y;
	size_t v;
	size_t node_size;
	Node **nodes;
} SOMap;

extern Node node;

extern SOMap map;

SOMap build_som(size_t v_size, size_t s_size);

void set_map_dimensions(SOMap *m, size_t sample_size);

double *get_random_vector(size_t v_size);

#endif // SOMAP_BUILDER_H_
