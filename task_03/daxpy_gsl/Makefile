CC = gcc

CFLAGS = -Wall -Wextra -O2 -I..
LDLIBS = -lgsl -lgslcblas -lm

all: create_x_y_gsl daxpy_gsl

create_x_y_gsl: create_x_y_gsl.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

daxpy_gsl: daxpy_gsl.c ../parser.h
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

run: all
	./create_x_y_gsl
	./daxpy_gsl

clean:
	rm -f create_x_y_gsl daxpy_gsl