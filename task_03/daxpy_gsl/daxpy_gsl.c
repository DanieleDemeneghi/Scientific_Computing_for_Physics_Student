#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "gsl/gsl_vector.h"

// Define structure to hold configuration data
typedef struct  {
    char file_x_vector[100];
    char file_y_vector[100];
    float a;
    int N;
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

        else if (strcmp(co->key, "N") == 0) {
            config->N = atoi(co->value);
        }

        

        co = co->prev;
    }

    return 0;

}

// Read and add vectors
void read_add_vectors(config_struct config) {

    //Initialize vectors
    gsl_vector *x = gsl_vector_alloc(config.N);
    gsl_vector *y = gsl_vector_alloc(config.N);

    //Open vector files
    FILE *file_x_vector_ptr = fopen(config.file_x_vector, "r");
    FILE *file_y_vector_ptr = fopen(config.file_y_vector, "r");

    //Read files to vectors
    gsl_vector_fscanf(file_x_vector_ptr, x);
    gsl_vector_fscanf(file_y_vector_ptr, y);

    // Add vectors
    gsl_vector_axpby(config.a, x, 1, y);

    //Write to file
    char file_d_vector_name[100];
    char prefix[] = "./outputdir/vector_N";

    snprintf(file_d_vector_name, sizeof(file_d_vector_name), "%s_%d_d.dat", prefix, config.N);
    FILE *file_d_vector_ptr;
    file_d_vector_ptr = fopen(file_d_vector_name, "w");

    gsl_vector_fprintf(file_d_vector_ptr, y, "%.5f");

    // Free memory and close files
    gsl_vector_free(x);
    gsl_vector_free(y);

    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);
    fclose(file_d_vector_ptr);

}

// Main program
int main() {

    config_struct config;
    char file_path[] = "./daxpy_gsl.conf";

    configurator_parser(file_path, &config);
    
    read_add_vectors(config);
    
    return 0;
}