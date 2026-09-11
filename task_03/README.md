# Folder content

A library "parser.h" to read data from .conf files

Each folder contains :
1) create_x_y_*.c file that saves the created vectors to a file, 
2) daxpy_*.c file that performs the calculations and saves the output.  the Makfile, the executables
3) daxpy_*.conf file with the input x and y filenames, and the parameter "a"
4) Makefiles
5) Script executables
6) Output folders or files

To change vector dimensions modify N inside
```c
int main() {
    int N = 100;
    create_file(N)
}
```
in the create_x_y_*.c files and adjust the file_*_vector names in the .conf files
```
file_x_vector = ./outputdir/vector_N_<insert_new_N_here>_x.dat
file_y_vector = ./outputdir/vector_N_<insert_new_N_here>_y.dat
```
Then compile and run the Makefiles with
```
make run
```
