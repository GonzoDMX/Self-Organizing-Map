/*
*	DATASET_BUILDER_H_
*	Created by: Andrew O'Shei
*	Date: Nov 1, 2021
*	
*	Info:
*	Header file and declarations for DATASET_BUILDER
*
*/



#ifndef DATASET_BUILDER_H_
#define DATASET_BUILDER_H_

typedef struct
{
	double *data;
	int color;
} Vector;

typedef struct
{
	size_t vector_size;
	size_t sample_size;
	double *min_values;
	double *max_values;
	Vector *vector;
} Dataset;

extern Vector vector;
extern Dataset data;

// Checks input file path and opens dataset file
FILE *open_dataset(const char *f_path);

// Central constructor for dataset, reads file line by line parsing vectors
Dataset build_dataset(const char *f_path);

// Request index of classification column
int get_class_column();

// Get a unique key for classification
int get_class_color(double val);

// Take a line from file and break values into a vector struct
Vector parse_vector(char *v_str, int classify);

// Initializes the parameters of the dataset (vector size and min / max arrays)
void init_data_params(Dataset *d);

// Updates the Min / Max values in the Dataset struct
void update_min_max(Dataset *data);

// Parses data elements from a string, for data strings we get a hash
double parse_data_elem(const char *elem);

// A simplistic hash function to create unique values representing strings
static int dumbHash(const char *str);


#endif // DATASET_BUILDER_H_
