CC = mpicc

CFLAGS = -Wall -Wextra -O2 -I..
LDLIBS = -lm

all: create_x_y daxpy_mpi

create_x_y: create_x_y.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

daxpy_mpi: daxpy_mpi.c ../parser.h
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

run: all
	./create_x_y
	mpiexec -n 4 ./daxpy_mpi

clean:
	rm -f create_x_y daxpy_mpi