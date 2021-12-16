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
#include <string.h>
#include <math.h>
#include <time.h>
#include "include/dataset_builder.h"
#include "include/dataset_operations.h"
#include "include/somap_builder.h"
#include "include/visualize.h"
#include "include/training.h"
#include "include/test_functions.h"
#include "include/request_params.h"


int main(int argc, char **argv)
{
	// Initialize / Seed random numbergenerator, DO THIS ONLY ONCE !
	srand(time(NULL));
	
	int debug = 0;
	int verbose = 0;
	
	// Check for path to dataset
	// if not available tell the user how the program works
	if (argc < 2)
	{
		printf("\nHint: You need to provide a path to a dataset as argument.\n");
		printf("\nUsage: %s <DATASET_PATH>\n\n", argv[0]);
		exit(1);
	}
	else if(argc == 3)
	{
		// Check for flags
		if(strcmp(argv[2], "-D") == 0)
		{
			// Enable Debug Mode
			debug = 1;
		}
		else if(strcmp(argv[2], "-V") == 0)
		{
			// Enable Verbose Training
			verbose = 1;
		}
		else
		{
			printf("\nUnknown flag %s, continuing normal program operation\n", argv[2]);
		}
	}
	
	// Load Dataset into memory
	Dataset d = build_dataset(argv[1]);
	
	if(debug)
	{
		// Print Dataset
		print_dataset(&d);
		press_enter_to_continue();
		
		// Print Size, Min and Max Values in Dataset
		print_sample_size(&d);
		print_vector_size(&d);
		print_min_values(&d);
		print_max_values(&d);
		press_enter_to_continue();
	}

	// Normalize the Data in Dataset	
	normalize_dataset(&d);
	if(debug)
	{
		print_dataset(&d);
		press_enter_to_continue();
		
		// Print the normalized average values of data vectors
		print_avg_values(&d);
		press_enter_to_continue();
	}
	
	size_t *dimensions = get_map_dimensions(d.sample_size);
	
	// Build a Node Map Initialized to random values
	SOMap m = build_som(dimensions, d.vector_size, d.sample_size, d.avg_values);
	free(dimensions);
	
	if(debug)
	{
		// Print the SOMap with its randomly initialized vectors
		print_node_map(&m);
		press_enter_to_continue();
	}
	
	// Set the iteration count and learning rate
	size_t iterations = get_iteration_count(d.vector_size);
	double learning_rate = get_learning_rate();
	double learning_delay = get_learning_delay();
	press_enter_to_continue();

	populate_feature_map(&d, &m);
	set_ett(&m);

	if(debug)
	{
		printf("\nPrint feature map (before training):\n");
		print_feature_map(&m);
		press_enter_to_continue();
	}
	
	// Write out the mapped dataset over the pre-trained SOMap
	// This is just for comparison with the final result
	write_ett_csv(&m, "csv/pre_ettiquette.csv");
	write_avg_csv(&m, "csv/outpre.csv");

	// Map radius is used for calculating the neighborhood size
	double map_radius = set_map_radius(m.x, m.y);
	
	// Time constant is used to set the decay of the neighborhood
	// In other words this sets the Training Phase 1 duration
	double time_constant = set_time_constant(iterations, map_radius);

	// printf("Time Constant: %lf\n", time_constant);

	// Enter Training Loop Here
	for (int t = 0; t < iterations; t++)
	{
		// Set the learning rate
		double l_rate = set_learning_rate(learning_rate, learning_delay, t, iterations);
		
		// Set neighborhood size over time
		double neighborhood = set_neighborhood_size(map_radius, t, time_constant);
		
		// Get randomized order of data for this epoch
		size_t *order;
		order = get_randomized_order(d.sample_size);
		
		// Get randomized order of data for this epoch
		// int rand_index = get_random_sample(d.sample_size);
		
		// Enter training loop
		for(size_t s = 0; s < d.sample_size; s++)
		{
			// Find the Best Match Unit		
			Node *bmu_node;
			bmu_node = get_best_match_unit(d.vector[order[s]].data, &m);
			
			// printf("BMU, Pos X: %ld | Pos Y: %ld\n", bmu_node->x, bmu_node->y);
			update_nodes(d.vector[order[s]].data, bmu_node, l_rate, neighborhood, &m);
		}
		
		// If Verbose mode enabled print training details
		if(verbose)
		{
			printf("Iteration Cycle: %d | ", t+1);
			printf("Neighborhood size: %lf | ", neighborhood);
			printf("N_Sq: %lf | ", (neighborhood * neighborhood));
			printf("Learning Rate: %lf", l_rate);
			printf("\n");
		}
	}
	
	// Print the trained Self-Organizing Map's vector values
	if(debug)
	{
		print_node_map(&m);
		press_enter_to_continue();
	}
	
	// Re-initialize the feature map
	reset_feature_map(&m);
	// Map the dataset over the trained SOMap
	populate_feature_map(&d, &m);
	set_ett(&m);
	
	// Print the mapped dataset
	printf("\nFeature map:\n");
	print_feature_map(&m);
	
	// Write out the mapped dataset to csv for visualization
	write_avg_csv(&m, "csv/output.csv");
	write_ett_csv(&m, "csv/ettiquette.csv");
	
	// Free the dataset from memory
	for(int i = 0; i < d.sample_size; i++)
	{
		free(d.vector[i].data);
	}
	free(d.vector);
	free(d.avg_values);
	free(d.min_values);
	free(d.max_values);


	// Free the SOM From memory
	for(int i = 0; i<m.y; i++)
	{
		for(int j =0; j<m.x; j++)
		{
			free(m.nodes[i][j].weights);
		}
		free(m.nodes[i]);
	}
	free(m.nodes);
	
	
	// Run visualization and handle errors
	int system_check = system("python visualize_csv.py");
	if(system_check == 40704)
	{
		system_check = system("python3 visualize_csv.py");
	}
	printf("System closed with status: %d\n\n", system_check);
	if(system_check == 32512)
	{
		printf("Hint:\tYou must install Python3 in order to visualize the SOMap.\n");
		return 0;
	}
	else if(system_check == 512)
	{
		printf("Hint:\tDid you move or modify the 'visualize_csv.py' script?\n");
		printf("\tIt must be located in the same directory as the 'somap' executable.\n");
		return 0;
	}
	return 0;
}






