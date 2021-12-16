/*
*	SOMAP_OPERATIONS
*	Created by: Andrew O'Shei
*	Date: Nov 2, 2021
*	
*	Info:
*	Functions for manipulating the SOM Node Network
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "include/dataset_builder.h"
#include "include/somap_builder.h"
#include "include/visualize.h"
#include "include/training.h"




int double_equals(double a, double b)
{
	double epsilon = 0.000001;
    if(fabs(a - b) < epsilon)
    {
    	return 1;
    }
    return 0;
}

// Find the best match unit at index
void get_all_match_unit(double *target, SOMap *m, int color)
{
	double dist=DBL_MAX, tmp, *weights;
	Node *bmu_node;
	bmu_node = get_best_match_unit(target, m);
	dist = multi_dimen_euclid_distance(target, bmu_node->weights, m->v);
	for (size_t i = 0; i < m->y; i++)
	{
		for (size_t j = 0; j < m->x; j++)
		{
			weights = m->nodes[i][j].weights;
			tmp = multi_dimen_euclid_distance(target, weights, m->v);
			if (double_equals(tmp, dist) == 1)
			{
				switch(color)
				{
					case 1:
						m->nodes[i][j].color[0]++;
						break;
					case 2:
						m->nodes[i][j].color[1]++;
						break;
					case 3:
						m->nodes[i][j].color[2]++;
						break;
				}
			}
		}
	}
}



double get_distance(size_t *pos, size_t *bmu_pos)
{
	double x_val, y_val;
	x_val = (double)((pos[0] - bmu_pos[0]) * (pos[0] - bmu_pos[0]));
	y_val = (double)((pos[1] - bmu_pos[1]) * (pos[1] - bmu_pos[1]));
	return sqrt(x_val + y_val);
}


void reset_feature_map(SOMap *m)
{
	for (size_t i = 0; i < m->y; i++)
	{
		for (size_t j = 0; j < m->x; j++)
		{
			m->nodes[i][j].color[0] = 0;
			m->nodes[i][j].color[1] = 0;
			m->nodes[i][j].color[2] = 0;
		}
	}
}


void populate_feature_map(Dataset *d, SOMap *m)
{
	for (size_t i = 0; i < d->sample_size; i++)
	{
		get_all_match_unit(d->vector[i].data, m, d->vector[i].color);
	}
}



void set_ett(SOMap *m)
{
	int max, index;
	for(int i = 0; i < m->y; i++)
	{
		for(int j = 0; j < m->x; j++)
		{
			max = 0;
			index = 0;
			for(int k = 0; k < 3; k++)
			{
				if(m->nodes[i][j].color[k] > max)
				{
					max = m->nodes[i][j].color[k];
					index = k + 1;
				}
			}
			m->nodes[i][j].ett = index;
		}
	}
}


// Writes a CSV file using the averages of Node Vector weights
int write_avg_csv(SOMap *m, char *f_path)
{
	// Write out node map as csv
	FILE *fp;
	fp = fopen(f_path, "w+");
	if(fp == NULL)
	{
		printf("Error generating CSV file");
		return 0;
	}
	// Write the CSV File Header
	write_csv_header(fp, m->x);
	// Iterate through nodes, write the average of their weights
	for (int i  = 0; i<m->y; i++){
			fprintf(fp, "\"%d\"", i);
		for (int j = 0; j<m->x; j++){
			fprintf(fp, ",%lf",	((m->nodes[i][j].weights[0] +
								m->nodes[i][j].weights[1] +
								m->nodes[i][j].weights[2] +
								m->nodes[i][j].weights[3]) / 4));
		}
		fprintf(fp,"\n");
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 1;	
}


// Writes a CSV File using node labels
int write_ett_csv(SOMap *m, char *f_path)
{
	// Write out node map as csv
	FILE *fp;
	fp = fopen(f_path, "w+");
	if(fp == NULL)
	{
		printf("Error generating CSV file");
		return 0;
	}
	// Write the CSV File Header
	write_csv_header(fp, m->x);
	// Iterate through nodes write their label value
	for (int i  = 0; i<m->y; i++){
			fprintf(fp, "\"%d\"", i);
		for (int j = 0; j<m->x; j++){
			fprintf(fp, ",%d",	m->nodes[i][j].ett);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 1;	
}

// Generate labels for the output CSV File
void write_csv_header(FILE *fp, size_t x)
{
	int count = 0;
	fprintf(fp, "\"x\",");
	while(count < x)
	{
		fprintf(fp, "\"%d\"", count);
		if((count + 1) != x)
		{
			fprintf(fp, ",");
		}
		count++;
	}
	fprintf(fp, "\n");
}

