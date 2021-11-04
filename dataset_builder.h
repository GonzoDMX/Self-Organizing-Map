/*
*
*	Header file for the dataset_builder.c module
*
*/



#ifndef DATASET_BUILDER_H_
#define DATASET_BUILDER_H_

typedef struct
{
	size_t vector_size;
	size_t sample_size;
	double *min_values;
	double *max_values;
	double **data;
} Dataset;

extern Dataset data;

// Checks input file path and opens dataset file
FILE *open_dataset(const char *f_path);

// Central constructor for dataset, reads file line by line parsing vectors
Dataset build_dataset(const char *f_path);

// Take a line from file and break values into a vector
double *parse_vector(const char *v_str, Dataset *data, int first);

// Initializes the parameters of the dataset (vector size and min / max arrays)
int init_data_params(const double *v, Dataset *data, size_t v_size);

// Updates the Min / Max values in the Dataset struct
void update_vector_min_max(const double *v, Dataset *data);

// Appends a vector to the Dataset struct and increments sample size
int append_vector(double *v, Dataset *data, int first);

// Parses data elements from a string, for data strings we get a hash
double parse_data_elem(const char *elem);

// A simplistic hash function to create unique values representing strings
static int dumbHash(const char *str);


#endif // DATASET_BUILDER_H_
