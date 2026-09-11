#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gsl/gsl_vector.h"


void create_file(int N) {
    
    // Create filenames
    char file_x_vector_name[100];    
    char file_y_vector_name[100];
    char prefix[] = "./outputdir/vector_N";
    
    snprintf(file_x_vector_name, sizeof(file_x_vector_name), "%s_%d_x.dat", prefix, N);
    snprintf(file_y_vector_name, sizeof(file_y_vector_name), "%s_%d_y.dat", prefix, N);
    
    // Create files
    FILE *file_x_vector_ptr;
    FILE *file_y_vector_ptr;

    file_x_vector_ptr= fopen(file_x_vector_name, "w");
    file_y_vector_ptr= fopen(file_y_vector_name, "w");

    // Create vectors
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *y = gsl_vector_alloc(N);

    // Initialize vectors
    double x_val = 0.1;
    double y_val = 7.1;

    gsl_vector_set_all(x, x_val);
    gsl_vector_set_all(y, y_val);

    // Write vectors to file
    gsl_vector_fprintf(file_x_vector_ptr, x, "%.10f");
    gsl_vector_fprintf(file_y_vector_ptr, y, "%.10f");

    // Free memory and close files
    gsl_vector_free(x);
    gsl_vector_free(y);

    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);

}

int main() {
    create_file(100);
}