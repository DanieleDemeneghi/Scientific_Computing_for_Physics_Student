#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Define structure to hold configuration data
typedef struct  {
    char file_x_vector[100];
    char file_y_vector[100];
    double a;
} config_struct;

// Parse configuration file data
int configurator_parser(char file_path[], config_struct *config) {
    
    config_option_t co;
    
    if ((co = read_config_file(file_path)) == NULL) {
        perror("read_config_file()");
        return -1;
    }
    while(co != NULL) {

        if (strcmp(co->key, "file_x_vector" ) == 0) {
            strcpy(config->file_x_vector, co->value);
        }

        else if (strcmp(co->key, "file_y_vector" ) == 0) {
            strcpy(config->file_y_vector, co->value);
        }
        
        else if (strcmp(co->key, "a") == 0) {
            config->a = atof(co->value);
       
        }

        co = co->prev;
    }

    return 0;

}

// Get vector dimension
int get_vector_dimension(FILE *file_vector) {
    
    int vector_dimension = 0;
    int ch;

    rewind(file_vector);

    while((ch = fgetc(file_vector)) != EOF) {
        if(ch == '\n') {
            vector_dimension++;
        }
    }

    rewind(file_vector);
    return vector_dimension;

}

// Build vector
void vector_builder(FILE *file_vector, double vector[]) {

    char vector_element[100];
    int i = 0;

    while(fgets(vector_element, sizeof(vector_element), file_vector)) {
        vector[i] = atof(vector_element);
        i++;
    }

}

// Vector Addition
void add_vector(double *x, double *y, double *d, int vector_dimension, double a) {
    
    for(int i = 0; i < vector_dimension; i++) {
        
        d[i] = a*x[i] + y[i];
    
    }
}


// Main program
int main() {

    // Parse configurator file content
    config_struct config;
    char file_path[] = "./daxpy.conf";

    configurator_parser(file_path, &config);

    // Open input files
    FILE *file_x_vector_ptr = fopen(config.file_x_vector, "r");
    FILE *file_y_vector_ptr = fopen(config.file_y_vector, "r");

    // Get dimension of x and y vectors
    int x_dimension = get_vector_dimension(file_x_vector_ptr);
    int y_dimension = get_vector_dimension(file_y_vector_ptr);

    // Allocate memory for x, y and d vectors
    double *x = malloc(x_dimension*sizeof(double));
    double *y = malloc(y_dimension*sizeof(double));
    double *d = malloc(x_dimension*sizeof(double));

    // Initialize x and y vector values
    vector_builder(file_x_vector_ptr, x);
    vector_builder(file_y_vector_ptr, y);

    // Add vectors
    add_vector(x, y, d, x_dimension, config.a);


    // Create output vector d filename
    char file_d_vector_name[100];
    char prefix[] = "./outputdir/vector_N";
    snprintf(file_d_vector_name, sizeof(file_d_vector_name), "%s_%d_d.dat", prefix, x_dimension);

    // Open output vector d filename
    FILE *file_d_vector_ptr;
    file_d_vector_ptr = fopen(file_d_vector_name, "w");

    // Write results to output vector d filename
    for (int i = 0; i < x_dimension; i++) {
        fprintf(file_d_vector_ptr, "%.10f\n", d[i]);
    }
    
    // Free up memory and close files
    free(x);
    free(y);
    free(d);

    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);
    fclose(file_d_vector_ptr);
    

}