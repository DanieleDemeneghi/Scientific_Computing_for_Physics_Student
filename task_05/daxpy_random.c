#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gsl/gsl_vector.h"
#include "gsl/gsl_rng.h"
#include "gsl/gsl_randist.h"

// Create and add random vectors
void create_add_random_vectors(int N, double a) {

    //Create file names
    char file_x_vector_name[100];    
    char file_y_vector_name[100];
    char file_d_vector_name[100];
    char prefix[] = "./outputdir/vector_N";
    
    snprintf(file_x_vector_name, sizeof(file_x_vector_name), "%s_%d_x.dat", prefix, N);
    snprintf(file_y_vector_name, sizeof(file_y_vector_name), "%s_%d_y.dat", prefix, N);
    snprintf(file_d_vector_name, sizeof(file_d_vector_name), "%s_%d_d.dat", prefix, N);
    
    // Create files
    FILE *file_x_vector_ptr;
    FILE *file_y_vector_ptr;
    FILE *file_d_vector_ptr;
    
    file_x_vector_ptr= fopen(file_x_vector_name, "w");
    file_y_vector_ptr= fopen(file_y_vector_name, "w");
    file_d_vector_ptr = fopen(file_d_vector_name, "w");
   
    //Allocate vectors
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *y = gsl_vector_alloc(N);

    //Set up random number generator
    const gsl_rng_type *T;
    gsl_rng *r;
    
    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, 12345);

    //Initialize vectors
    for (int i = 0; i < N; i++) {
        
        gsl_vector_set(x, i, gsl_ran_gaussian(r, 1.0));
        gsl_vector_set(y, i, gsl_ran_gaussian(r, 1.0));
    
    }
   
    //Save vectors to file
    gsl_vector_fprintf(file_x_vector_ptr, x, "%.16f");
    gsl_vector_fprintf(file_y_vector_ptr, y, "%.16f");

    // Add vectors
    gsl_vector_axpby(a, x, 1, y);

    
    //Write to file
    gsl_vector_fprintf(file_d_vector_ptr, y, "%.16f");

    //Free up memory and close files
    gsl_vector_free(x);
    gsl_vector_free(y);

    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);
    fclose(file_d_vector_ptr);


}


int main() {
    
    create_add_random_vectors(100, 3.0);



}