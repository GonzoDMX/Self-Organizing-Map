/*
*
*
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

SOMap build_som(size_t v_size);

void get_map_dimensions(SOMap *m);

double *get_random_vector(size_t v_size);

#endif // SOMAP_BUILDER_H_
