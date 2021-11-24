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
#include "dataset_builder.h"
#include "somap_builder.h"
#include "test_functions.h"


void print_dataset(Dataset *d)
{
	printf("\nDataset values: \n");
	for (int i = 0; i < d->sample_size; i++)
	{
		if ((i+1) > 99999) 	  { printf("%d: | ", i+1);		}
		else if ((i+1) > 9999){ printf(" %d: | ", i+1);     }
		else if ((i+1) > 999) { printf("  %d: | ", i+1);    }
		else if ((i+1) > 99)  { printf("   %d: | ", i+1);   }
		else if ((i+1) > 9)   { printf("    %d: | ", i+1);  }
		else 				  { printf("     %d: | ", i+1); }
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
		if (o[i] > 99999) 	{ printf("%ld| ", o[i]);	 }
		else if(o[i] > 9999){ printf("%ld | ", o[i]);	 }
		else if(o[i] > 999)	{ printf("%ld  | ", o[i]);   }
		else if(o[i] > 99) 	{ printf("%ld   | ", o[i]);  }
		else if(o[i] > 9) 	{ printf("%ld    | ", o[i]); }
		else 				{ printf("%ld     | ", o[i]);}
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
			size_t tmp = m->nodes[i][j].color;
			if (tmp > 99) 		{ printf("%ld | ", tmp);  }
			else if (tmp > 9) 	{ printf(" %ld | ", tmp); }
			else 				{ printf("  %ld | ", tmp);}
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
