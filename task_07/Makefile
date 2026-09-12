CC = gcc
CFLAGS = -Wall -Wextra -O2 -I..
LDLIBS = -lm

all: run

create_x_y: create_x_y.c
	$(CC) $(CFLAGS) create_x_y.c -o create_x_y $(LDLIBS)

daxpy: daxpy.c parser.h
	$(CC) $(CFLAGS) daxpy.c -o daxpy $(LDLIBS)

run: create_x_y daxpy
	./create_x_y
	./daxpy

clean:
	rm -f create_x_y daxpy