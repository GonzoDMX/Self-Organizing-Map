/*
*	MAIN
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	Main program function for Self-Organizing Map Program
*
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
	
	// TODO Allow user to set dimensions of matrix, if no default to built in value
	
	// Build a Node Map Initialized to random values
	SOMap m = build_som(d.vector_size, d.sample_size);
	press_enter_to_continue();
	print_node_map(&m);
	press_enter_to_continue();
	
	
	size_t iter = get_iteration_count(d.vector_size);
	set_learning_rate();
	press_enter_to_continue();

	// Get a random order to process data samples
	//size_t *order;
	
	// The function returns an array of size_t
	//order = get_randomized_order(d.sample_size);
	//print_size_t_array(order, d.sample_size);
	//press_enter_to_continue();
	
	printf("\nPrint feature map (before training):\n");
	populate_feature_map(&d, &m);
	print_feature_map(&m);	
	
	press_enter_to_continue();
	
	// Train the SOM Here
	printf("\nStarting training of SOM\n");
	for (size_t i = 0; i < iter; i++)
	{
		printf("Pass: %ld\n", i+1);
		size_t *order;
		order = get_randomized_order(d.sample_size);
		update_learning_rate(i, iter);
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
	
	// Reset color value
	reset_feature_map(&m);
	
	printf("\nPrint feature map:\n");
	populate_feature_map(&d, &m);
	print_feature_map(&m);
}






