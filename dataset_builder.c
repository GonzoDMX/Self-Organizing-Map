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


static size_t vector_size = 0;


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
	int classify;
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
	
	classify = get_class_column();
	
	// tmp holds current char from file, i is index for substring
	// first is flag for first pass of function
	int tmp, i=0, first=1;
	// tmp_char holds a substring (a line) from file
	// with .data files each line is a vector
	char tmp_char[512];
	int counter = 0;
	Vector vect, *v_tmp;
	d.vector = malloc(sizeof(Vector));
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
				vect = parse_vector(tmp_char, classify);
				d.sample_size++;
				v_tmp = (Vector*)realloc(d.vector, sizeof(Vector)*d.sample_size);
				if(v_tmp == NULL)
				{
					printf("ERROR: Failed to allocate vector in Dataset");
					exit(1);
				}
				else
				{
					d.vector = v_tmp;
					d.vector[d.sample_size-1] = vect;
				}
				// If first initialize parameters
				if(first == 1)
				{
					init_data_params(&d);
					first = 0;
				}
				// Set Min / Max Vector Values
				else
				{
					update_min_max(&d);
				}
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


// Request index of classification column
int get_class_column()
{
	int col;
	while(1)
	{
		printf("\nWhich column in the dataset is designated for classification?\n");
		scanf("%d", &col);
		if(col > 0)
		{
			getchar();
			printf("Column %d is designated for classification.\n", col);
			break;
		}
		printf("\nERROR: Invalid column index.\n");
	}
	return col-1;
}


// Receives value from the designated classifier column
// A key value that corresponds with its category is returned
int get_class_color(double val)
{
	static double colors[64];
	static int c_size;
	int i;
	if(c_size == 0)
	{
		colors[c_size++] = val;
		return c_size;
	}
	else
	{
		for(i = 0; i < c_size; i++)
		{
			if(colors[i] == val)
			{
				return (i+1);
			}
		}
		colors[c_size++] = val;
	}
	return c_size;
}


Vector parse_vector(char *v_str, int classify)
{
	Vector vect;
	double *v, *v_tmp, tmp;
	int count=0, mod=0;
	char *val;
	// Initialize vector
	v = malloc(sizeof(double));	
	while(1)
	{
		if(count == 0)
		{
			val = strtok(v_str, ",");
		}
		else
		{
			val = strtok(NULL, ",");
		}
		if(val == NULL)
		{
			break;
		}
		// Get string value as double
		tmp = parse_data_elem(val);
		if(classify == count)
		{
			// Set the data color value here
			vect.color = get_class_color(tmp);
			mod=1;
		}
		else
		{
			v_tmp = realloc(v, sizeof(double)*count+1);
			if(v_tmp == NULL)
			{
				printf("ERROR: Failed to realloc vector data\n");
				exit(1);
			}
			v = v_tmp;
			v[count-mod] = tmp;
		}
		count++;
	}
	if(count == 0)
	{
		printf("ERROR: No data in vector\n");
		exit(1);
	}
	// Set data vector data values here
	vect.data = v;
	
	// Set and test vector size against global
	if(vector_size == 0)
	{
		vector_size = count-1;
	}
	if(vector_size != count-1)
	{
		printf("ERROR: Not all data is the same size");
		exit(1);
	}
	/*
	printf("--Test Vector--\n");
	printf("Data: | ");
	for(int i = 0; i < vector_size; i++)
	{
		printf("%lf | ", vect.data[i]);
	}
	printf("\n");
	printf("Color: %d\n", vect.color);
	*/
	return vect;
}

		

// Build params for vector size, min and max values (used later for normalization)
void init_data_params(Dataset *d)
{
	d->vector_size = vector_size;
	d->min_values = (double*)malloc(sizeof(double) * d->vector_size);
	d->max_values = (double*)malloc(sizeof(double) * d->vector_size);
	if (d->min_values == NULL || d->max_values == NULL)
	{
		// Check that memory is properly allocated
		free(d->min_values);
		free(d->max_values);
		printf("ERROR: Failed to allocate Min/Max Vectors\n");
		exit(1);
	}
	for (int i = 0; i < d->vector_size; i++)
	{
		d->min_values[i] = d->vector[0].data[i];
		d->max_values[i] = d->vector[0].data[i];
	}
}


// Check / Set min and max values with new vector
void update_min_max(Dataset *d)
{
	int ind = d->sample_size-1;
	for (int i = 0; i < d->vector_size; i++)
	{
		if (d->vector[ind].data[i] < d->min_values[i])
		{
			d->min_values[i] = d->vector[ind].data[i];
		}
		else if (d->vector[ind].data[i] > d->max_values[i])
		{
			d->max_values[i] = d->vector[ind].data[i];
		}
	}
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


