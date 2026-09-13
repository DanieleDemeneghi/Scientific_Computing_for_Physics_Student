To change vector dimensions modify N inside

```c

int main() {

	int N = 10000000;

	create\_file(N)

}

```

in the ```create_x_y_.c``` files and adjust the ```file_vector_names``` in the ```.conf``` files

```

file_x_vector = ./outputdir/vector_N_<insert_new_N_here>_x.dat

file_y_vector = ./outputdir/vector_N_<insert_new_N_here>_y.dat

```

Then compile and run the Makefile with

```

make run

```



