/*
*	TEST_FUNCTIONS
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	Series of helper functions for printing data structures in terminal
*
*/



#include <stdio.h>
#include "include/dataset_builder.h"
#include "include/somap_builder.h"
#include "include/test_functions.h"


void print_dataset(Dataset *d)
{
	printf("\nDataset values: \n");
	for (int i = 0; i < d->sample_size; i++)
	{
		printf("%-5d: | ", i+1);
		for (int j = 0; j < d->vector_size; j++)
		{
			printf("%lf | ", d->vector[i].data[j]);
		}
		printf("Color: %d", d->vector[i].color);
		printf("\n");
	}
}


void print_sample_size(Dataset *d)
{
	printf("\nNumber of samples in dataset: %ld\n", d->sample_size);
}


void print_vector_size(Dataset *d)
{
	printf("\nNumber of elements in each data vector: %ld\n", d->vector_size);
}


void print_min_values(Dataset *d)
{
	printf("\nVector Min Values: | ");
	for (int i = 0; i < d->vector_size; i++)
	{
		printf("%lf | ", d->min_values[i]);
	}
	printf("\n");
}


void print_max_values(Dataset *d)
{
	printf("\nVector Max Values: | ");
	for (int i = 0; i < d->vector_size; i++)
	{
		printf("%lf | ", d->max_values[i]);
	}
	printf("\n");
}


void print_avg_values(Dataset *d)
{
	printf("\nVector Avg Values: | ");
	for (int i = 0; i < d->vector_size; i++)
	{
		printf("%lf | ", d->avg_values[i]);
	}
	printf("\n");
}

void print_node_map(SOMap *m)
{
	printf("\nNode Map:\n");
	for (int i = 0; i < m->y; i++)
	{
		for (int j = 0; j < m->x; j++)
		{
			printf("{ %d, %d }: | ", j, i);
			for (int k = 0; k < m->v; k++)
			{
				printf("%lf | ", m->nodes[i][j].weights[k]);
			}
			printf("\n");
		}
	}
	printf("\n");
}


void print_size_t_array(size_t *o, size_t s)
{
	int count = 0;
	printf("\nRandomly ordered list:\n");
	for (size_t i = 0; i < s; i++)
	{
		if (count == 0) { printf("| "); }
		else { printf("%-5ld | ", o[i]); }
		count++;
		if (count == 10)
		{
			printf("\n");
			count=0;
		}
	}
	printf("\n");
}


void print_feature_map(SOMap *m)
{
	for (size_t i = 0; i < m->y; i++)
	{
		printf(" | ");
		for (size_t j = 0; j < m->x; j++)
		{
			printf(" %-2d |", m->nodes[i][j].ett);
		}
		printf("\n");
	}
}

void print_avg_map(SOMap *m)
{
	for (size_t i = 0; i < m->y; i++)
	{
		printf(" | ");
		for (size_t j = 0; j < m->x; j++)
		{
			double tmp = (m->nodes[i][j].weights[0] +
						 m->nodes[i][j].weights[1] +
						 m->nodes[i][j].weights[2] +
						 m->nodes[i][j].weights[3]) / 4;
			printf(" %-2lf ", tmp);
			printf(" |");
		}
		printf("\n");
	}
}


void press_enter_to_continue()
{
	int enter = 0;
	printf("\n---Press [ENTER] to continue---");
	while (enter != '\r' && enter != '\n')
	{
		enter = getchar(); 
	}
}








