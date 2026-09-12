CC = gcc
CFLAGS = -Wall -Wextra -O2 -I..
LDLIBS = -lm

all: run

create_x_y: create_x_y.c
	$(CC) $(CFLAGS) create_x_y.c -o create_x_y $(LDLIBS)

daxpy: daxpy_chunck.c parser.h
	$(CC) $(CFLAGS) daxpy_chunck.c -o daxpy_chunck $(LDLIBS)

run: create_x_y daxpy_chunck
	./create_x_y
	./daxpy_chunck

clean:
	rm -f create_x_y daxpy_chunck