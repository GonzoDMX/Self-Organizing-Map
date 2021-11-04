/*
*
*	Main Program function for constructing a Self Organizing Map
*	Created by: Andrew O'Shei
*/


#include <stdio.h>
#include <stdlib.h>
#include "dataset_builder.h"
#include "dataset_operations.h"
#include "somap_builder.h"
#include "somap_operations.h"
#include "test_functions.h"


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("\nUsage: %s <DATASET_PATH>\n\n", argv[0]);
		exit(1);
	}
	// Load Dataset into memory
	Dataset d = build_dataset(argv[1]);
	
	// Print Dataset
	print_dataset(&d);
	press_enter_to_continue();
	
	// Print Size, Min and Max Values in Dataset
	print_sample_size(&d);
	print_vector_size(&d);
	print_min_values(&d);
	print_max_values(&d);
	press_enter_to_continue();

	// Normalize the Data in Dataset	
	normalize_dataset(&d);
	print_dataset(&d);
	press_enter_to_continue();
	
	// Build a Node Map Initialized to random values
	SOMap m = build_som(d.vector_size);
	print_node_map(&m);
	press_enter_to_continue();
	
	size_t iter;
	iter = get_iteration_count();
	press_enter_to_continue();
	
	// Get a random order to process data samples
	//size_t *order;
	
	// The function returns an array of size_t
	//order = get_randomized_order(d.sample_size);
	//print_size_t_array(order, d.sample_size);
	//press_enter_to_continue();
	
	// Loop through Iterations
	printf("\nStarting training of SOM\n");
	for (size_t i = 0; i < iter; i++)
	{
		printf("Pass: %ld\n", i+1);
		size_t *order;
		order = get_randomized_order(d.sample_size);
		// Loop through samples
		for (size_t j = 0; j < d.sample_size; j++)
		{
			size_t *bmu_pos;
			bmu_pos = get_best_match_unit(&d, &m, order[j]);
			update_nodes(&d, &m, order[j], bmu_pos, i, iter);
		}
	}
	printf("\nTrainging complete!\n");
	
	print_node_map(&m);
	press_enter_to_continue();
	
	// size_t *pos;
	// pos = get_best_match_unit(&d, &m, order[0]);
	// printf("\nBest Match Unit: { %ld, %ld }\n", pos[0], pos[1]);
	
	printf("\nPrint feature map:\n");
	for (size_t i = 0; i < d.sample_size; i++)
	{
		size_t *pos;
		pos = get_best_match_unit(&d, &m, i);
		m.nodes[pos[1]][pos[0]].color += 1;
	}
	
	for (size_t i = 0; i < m.y; i++)
	{
		printf(" | ");
		for (size_t j = 0; j < m.x; j++)
		{
			size_t tmp = m.nodes[i][j].color;
			if (tmp > 99) 		{ printf("%ld | ", tmp);  }
			else if (tmp > 9) 	{ printf(" %ld | ", tmp); }
			else 				{ printf("  %ld | ", tmp);}
		}
		printf("\n");
	}
}






