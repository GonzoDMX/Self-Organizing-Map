CC=gcc
LIBS=-lm
SDIR=src
IDIR=src/include
ODIR=src/obj
CDIR=csv

CFLAGS=-I.$(IDIR) -Wall

_DEPS =	dataset_builder.h \
		dataset_operations.h \
		somap_builder.h \
		test_funcitons.h \
		request_params.h \
		visualize.h \
		training.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
		
_OBJ = 	main.o \
		dataset_builder.o \
		dataset_operations.o \
		somap_builder.o \
		test_functions.o \
		request_params.o \
		visualize.o \
		training.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Compiles each of the object files as separate targets
$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(ODIR) $(CDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
somap: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
