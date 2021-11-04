CC=gcc
CFLAGS=-I.

main: main.o dataset_builder.o dataset_operations.o somap_builder.o somap_operations.o test_functions.o
	$(CC) -o som_test main.o dataset_builder.o dataset_operations.o somap_builder.o somap_operations.o test_functions.o -lm
