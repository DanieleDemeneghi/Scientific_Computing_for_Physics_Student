#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
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
void add_vector_parallel(double *x, double *y, double *d, int vector_dimension, double a) {

    #pragma omp parallel for    
    for(int i = 0; i < vector_dimension; i++) {
        
        d[i] = a*x[i] + y[i];
    
    }
}

void add_vector_serial(double *x, double *y, double *d, int vector_dimension, double a) {


    for(int i = 0; i < vector_dimension; i++) {
        
        d[i] = a*x[i] + y[i];
    
    }
}



// Main program
int main() {

    omp_set_num_threads(4);

    config_struct config;
    char file_path[] = "./daxpy_openmp.conf";

    configurator_parser(file_path, &config);
    
    FILE *file_x_vector_ptr = fopen(config.file_x_vector, "r");
    FILE *file_y_vector_ptr = fopen(config.file_y_vector, "r");

    int x_dimension = get_vector_dimension(file_x_vector_ptr);
    int y_dimension = get_vector_dimension(file_y_vector_ptr);

    double *x = malloc(x_dimension*sizeof(double));
    double *y = malloc(y_dimension*sizeof(double));

    vector_builder(file_x_vector_ptr, x);
    vector_builder(file_y_vector_ptr, y);

    double *d_serial = malloc(x_dimension*sizeof(double));
    double *d_parallel = malloc(x_dimension*sizeof(double));

    // Add vectors serial
    double start_time_serial = omp_get_wtime();

    add_vector_serial(x, y, d_serial, x_dimension, config.a);

    double run_time_serial = (omp_get_wtime() - start_time_serial)*1000;

    printf("add_vector_serial completed in %.13f ms \n", run_time_serial);

    // Add vectors parallel
    double start_time_parallel = omp_get_wtime();

    add_vector_parallel(x, y, d_parallel, x_dimension, config.a);

    double run_time_parallel = (omp_get_wtime() - start_time_parallel)*1000;

    printf("add_vector_parallel for loop completed in %.13f ms \n", run_time_parallel);
    
    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);
  

    free(x);
    free(y);
    free(d_serial);
    free(d_parallel);
    

}