/*
*	DATASET_BUILDER
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	Builds a dataset struct from the dataset file passed to the constructor function
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "dataset_builder.h"

static int c=0;

// Check file path and then open the file
FILE *open_dataset(const char *f_path)
{
	char actualpath[PATH_MAX+1];
	// Check filepath
	if (realpath(f_path, actualpath) == NULL)
	{
		return NULL;
	}
	
	// Open the file
	FILE *fp;
	fp = fopen(actualpath, "r");
	if (fp == NULL)
	{
		return NULL;
	}
	return fp;
}

// Function that builds the dataset
Dataset build_dataset(const char *f_path)
{
	// Initialize Dataset Struct
	Dataset d;
	d.vector_size = 0;
	d.sample_size = 0;

	// Verify file path before continuing operation
	FILE *f;
	f = open_dataset(f_path);
	if (f == NULL)
	{
		// If NULL return empty dataset
		return d;
	}

	// tmp holds current char from file, i is index for substring
	// first is flag for first pass of function
	int tmp, i=0, first=1;
	// tmp_char holds a substring (a line) from file
	// with .data files each line is a vector
	char tmp_char[512];
	// vector holds the currently constructed vector
	double *vector;
	while (tmp = fgetc(f))
	{
		// When we hit a linebreak build vector from substring
		if (tmp == '\n')
		{
			// close the substring
			tmp_char[i] = '\0';
			// Filter out any empty strings
			if (tmp_char[0] != '\0')
			{
				// get the vector as a double array from substring
				vector = parse_vector(tmp_char, &d, first);
				if (vector != NULL)
				{
					i = append_vector(vector, &d, first);
					if (i == 0)
					{
						printf("Failed to append vector %ld\n", d.sample_size);
					}
				}
				if (first) { first--; }
			}
			i = 0;
		}
		else if (tmp == EOF)
		{
			break;
		}
		else
		{
			tmp_char[i] = tmp;
			i++;
		}
	}
	fclose(f);
	return d;
}


// Break string into a data vector
double *parse_vector(const char *v_str, Dataset *d, int first)
{
	double *v, *v_tmp;
	size_t v_size=0;
	int index=0, ind=0;
	char tmp_char[32];
	v = (double*)malloc(sizeof(double));
	while(1)
	{
		if (v_str[index] == ',' || v_str[index] =='\0')
		{
			tmp_char[ind] = '\0';
			ind = 0;
			v_tmp = (double*)realloc(v, sizeof(double) * ++v_size);
			if (v_tmp == NULL)
			{
				free(v_tmp);
				return NULL;
			}
			v = v_tmp;
			v[v_size-1] = parse_data_elem(tmp_char);
			if (v_str[index] == '\0')
			{
				break;
			}
		}
		else
		{
			tmp_char[ind] = v_str[index];
			ind++;
		}
		index++;
	}
	if (first)
	{
		index = init_data_params(v, d, v_size);
		if (index == 0)
		{
			return NULL;
		}
	}
	else
	{
		update_vector_min_max(v, d);
	}
	return v;
}


// Build params for vector size, min and max values (used later for normalization)
int init_data_params(const double *v, Dataset *d, size_t v_size)
{
	d->vector_size = v_size;
	d->min_values = (double*)malloc(sizeof(double) * v_size);
	d->max_values = (double*)malloc(sizeof(double) * v_size);
	if (d->min_values == NULL || d->max_values == NULL)
	{
		// Check that memory is properly allocated
		free(d->min_values);
		free(d->max_values);
		return 0;
	}
	for (int i = 0; i < v_size; i++)
	{
		d->min_values[i] = v[i];
		d->max_values[i] = v[i];
	}
	return 1;
}



// Check / Set min and max values with new vector
void update_vector_min_max(const double *v, Dataset *d)
{
	for (int i = 0; i < d->vector_size; i++)
	{
		if (v[i] < d->min_values[i])
		{
			d->min_values[i] = v[i];
		}
		else if (v[i] > d->max_values[i])
		{
			d->max_values[i] = v[i];
		}
	}
}


// Add incoming vector to the dataset
int append_vector(double *v, Dataset *d, int first)
{
	double **tmp_d;
	if (first)
	{
		d->data = (double**)malloc(sizeof(double));
	}
	else
	{
		tmp_d = (double**)realloc(d->data, sizeof(double) * d->sample_size + 1);
		if (tmp_d == NULL)
		{
			free(tmp_d);
			return 0;
		}
		d->data = tmp_d;
	}
	d->data[d->sample_size] = v;
	d->sample_size++;
	return 1;
}


// Parse data elements from dataset
// For numerical data convertt to a double
// For strings generate a unique value
double parse_data_elem(const char *elem)
{
	char *end_ptr;
	double val = strtod(elem, &end_ptr);
	int sum=0, index=0;
	if (val > 0)
	{
		return val;
	}
	else
	{
		while (elem[index] != '\0')
		{
			// Crude way of validating true 0 values
			if (elem[index] != '0' || elem[index] != '.')
			{
				return (double)dumbHash(elem) / 1000000;
			}
			index += 1;
		}
		return val;
	}
}

// Very basic attempt at seperating unique strings
// Will handle simple cases like paramutations
// But in large sets of unique strings expect some collisions
static int dumbHash(const char *str)
{
	int hash = 0;
	while (*str != '\0')
	{
		char c = *str++;
		int a = c - '!';
		hash = (hash * 2) + a;
	}
	return hash;
}


