CC = gcc

CFLAGS = -Wall -Wextra -O2 -I..
LDLIBS = -lhdf5 -lm

all: create_x_y_hdf daxpy_hdf

create_x_y_hdf: create_x_y_hdf.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

daxpy_hdf: daxpy_hdf.c ../parser.h
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

run: all
	./create_x_y_hdf
	./daxpy_hdf

clean:
	rm -f create_x_y_hdf daxpy_hdf