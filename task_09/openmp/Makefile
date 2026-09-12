CC = gcc

CFLAGS = -Wall -Wextra -O2 -I..
LDLIBS = -lm
OMPFLAGS = -fopenmp

all: run

create_x_y: create_x_y.c
	$(CC) $(CFLAGS) create_x_y.c -o create_x_y $(LDLIBS)

daxpy_openmp: daxpy_openmp.c ../parser.h
	$(CC) $(CFLAGS) $(OMPFLAGS) daxpy_openmp.c -o daxpy_openmp $(LDLIBS)

run: create_x_y daxpy_openmp
	./create_x_y
	./daxpy_openmp

clean:
	rm -f create_x_y daxpy_openmp