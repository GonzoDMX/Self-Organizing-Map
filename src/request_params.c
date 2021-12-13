/*
*	REQUEST_PARAMS
*	Created by: Andrew O'Shei
*	Date: Dec 13, 2021
*	
*	Info:
*	Functions to allow user to set training parameters
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/request_params.h"


// Function for setting the SOMap dimensions
size_t *get_map_dimensions(size_t sample_size)
{
	size_t *dimens;
	char choice;
	while(1)
	{
		printf("\nWould you like to manually set the SOM network dimensions (y or n)?\n");
		scanf("%c", &choice);
		
		if(choice == 'n')
		{
			printf("\nCalculating SOMap dimensions...\n");
			dimens = auto_dimensions(sample_size);
			break;
		}
		else if(choice == 'y')
		{
			dimens = malloc(sizeof(size_t) * 2);
			printf("\nWhat is the X dimension of the SOMap?\n");
			scanf("%ld", &dimens[0]);
			if(dimens[0] > 1)
			{
				printf("\nWhat is the Y dimension of the SOMap?\n");
				scanf("%ld", &dimens[1]);
				if(dimens[1] > 1)
				{
					break;
				}
			}
			printf("\nInvalid Input: Dimensions must be a whole number greater than 2\n");
		}
		printf("\nInvalid Choice: Enter either 'y' for yes or 'n' for non.\n");
	}
	printf("Number of Nodes: %ld\n", (dimens[0] * dimens[1]));
	printf("x: %ld | y: %ld\n", dimens[0], dimens[1]);
	return dimens;
}


// Set SOMap Dimensions automatically based on number of nodes
size_t *auto_dimensions(size_t sample_size)
{
	size_t *dimens, n;
	dimens = malloc(sizeof(size_t) * 2);
	n = 5 * sqrt(sample_size);
	dimens[0] = sqrt(n);
	while(1)
	{
		if(n % dimens[0] == 0)
		{
			dimens[1] = n / dimens[0];
			if(dimens[1] > 4 || dimens[0] == dimens[1])
			{
				break;
			}
			dimens[0] = sqrt(--n);
		}
		else
		{
			dimens[0]++;
		}
	}
	return dimens;
}


// Request the nmber of training iterations
size_t get_iteration_count(size_t v_size)
{
	size_t x;
	while(1)
	{
		printf("\nIn how many cycles would you like to train the SOM?\n");
		printf("Hint:\tEnter 0 for automatc value\n");
		scanf("%ld", &x);
		
		if (x >= 0)
		{
			getchar();
			if(x == 0)
			{
				printf("Default cycle count selected.\n");
				x = 5 * v_size * 100;
			}
			printf("Preparing to train the SOM for %ld iterations.\n", x);
			break;
		}
		printf("\nERROR: Number of iterations must be a whole number greater than 0.\n");
	}
	return x;
}


// Request the starting learning rate
double get_learning_rate()
{
	double r;
	while(1)
	{
		printf("\nPlease enter the starting learning rate:\n");
		printf("Hint:\tMust be a value between 0.0 and 1.0\n");
		scanf("%lf", &r);
		if(r > 0 && r <= 1.0)
		{
			getchar();
			printf("Learning rate set to: %lf\n", r);
			break;
		}
		printf("\nERROR: Invalid learning rate.\n");
	}
	return r;
}


// Request the starting learning rate delay
double get_learning_delay()
{
	double r;
	while(1)
	{
		printf("\nPlease enter the learning rate delay (0 = Default, 0.1 = Max):\n");
		printf("Hint: Values approaching 0 prodduce a more linear decay (default = 0.0001)\n");
		printf("\tAs the value increases the delay goes exponential (0.1 = Max)\n");
		scanf("%lf", &r);
		if(r > 0.0 && r <= 0.1)
		{
			getchar();
			printf("Learning rate delay set to: %lf\n", r);
			break;
		}
		if(r == 0)
		{
			r = 0.0001;
			getchar();
			printf("Learning rate delay set to default: %lf\n", r);
			break;
		}
		printf("\nERROR:\tInvalid learning rate delay.\n");
		printf("Hint:\tValue must be > 0 and <= 1.0\n");
	}
	return r;
}
