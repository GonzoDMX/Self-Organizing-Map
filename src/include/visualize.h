/*
*	VISUALIZE_H_
*	Created by: Andrew O'Shei
*	Date: Nov 2, 2021
*	
*	Info:
*	Header file for SOMAP Visualization
*
*/


#ifndef VISUALIZE_H_
#define VISUALIZE_H_


int double_equals(double a, double b);

void get_all_match_unit(double *target, SOMap *m, int color);

double get_distance(size_t *pos, size_t *bmu_pos);

void reset_feature_map(SOMap *m);

void populate_feature_map(Dataset *d, SOMap *m);

void set_ett(SOMap *m);

// Writes a CSV file using the averages of Node Vector weights
int write_avg_csv(SOMap *m, char *f_path);

// Writes a CSV File using node labels
int write_ett_csv(SOMap *m, char *f_path);

// Generate labels for the output CSV File
void write_csv_header(FILE *fp, size_t x);

#endif // SOMAP_OPERATIONS_H_
