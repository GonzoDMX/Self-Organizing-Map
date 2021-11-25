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
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <error.h>
#include "dataset_builder.h"


static size_t vector_size = 0;
static long file_size = 0;



// Function that builds the dataset
Dataset build_dataset(const char *f_path)
{	
	// Initialize Dataset Struct
	Dataset d;
	int classify=5, first=1;;
	d.vector_size = 0;
	d.sample_size = 0;

	classify = get_class_column();

	char *f_mem, *f_line, *save_ptr;
	
	f_mem = map_file_to_mem(f_path);
	
	Vector vect, *v_tmp;
	d.vector = malloc(sizeof(Vector));
	int count=0;
	while(1)
	{
		if(count == 0)
		{
			f_line = strtok_r(f_mem, "\n", &save_ptr);
		}
		else
		{
			f_line = strtok_r(NULL, "\n", &save_ptr);
		}
		if(f_line == NULL)
		{
			break;
		}
		// get the vector as a double array from substring
		vect = parse_vector(f_line, classify);
		d.sample_size++;
		v_tmp = (Vector*)realloc(d.vector, sizeof(Vector)*d.sample_size);
		if(v_tmp == NULL)
		{
			error(1, 105, "Failed to allocate vector %ld in Dataset\n", d.sample_size);
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
		count++;
	}
	munmap(f_mem, file_size);
	return d;
}


// Map the incoming Dataset file to memory, and test if successful
char *map_file_to_mem(const char *f_path)
{
	char *f_mem;
	char actual_path[PATH_MAX+1];
	
	if(realpath(f_path, actual_path) == NULL)
	{
		error(1, 2, "Failed to locate file %s\n", f_path);
	}
	
	int fp = open(actual_path, O_RDWR, S_IRUSR | S_IWUSR);
	struct stat sp;

	if(fstat(fp, &sp) == -1)
	{
		error(1, 2, "Failed to open dataset at location: %s\n", f_path);
	}
	// Set file size
	file_size = sp.st_size;
	
	f_mem = mmap(NULL, sp.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fp, 0);
	if(f_mem == MAP_FAILED)
	{
		error(1, 12, "Failed to map file to memory\n");
	}
	close(fp);
	return f_mem;
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


// Parse an individual Data Vector
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
				error(1, 105, "Failed to realloc vector data\n");
			}
			v = v_tmp;
			v[count-mod] = tmp;
		}
		count++;
	}
	if(count == 0)
	{
		error(1, 61, "No data in vector\n");
	}
	// Set data vector data values here
	vect.data = v;
	
	// Set and test vector size against global
	if(vector_size == 0)
	{
		vector_size = count-1;
		if(classify > vector_size)
		{
			error(1, 22, "Classification column index out of range\n");
		}
	}
	if(vector_size != count-1)
	{
		error(1, 84, "Cannot process vectors of mixed size\n");
	}
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
		error(1, 12, "Failed to allocate Min/Max Vectors\n");
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


