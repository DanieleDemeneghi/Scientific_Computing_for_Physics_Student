#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
void vector_builder(FILE *file_vector, double *vector) {

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

//CHUNKED ADDITION IMPLEMENTATION   
//Minimum Estimation
int min(int a, int b) {
    if(a < b) {
        return a;
    } else if (b < a) {
        return b;
    } else {
        return a;
    }
}

//Sum
double sum_func(double *d, int n) {

    double sum = 0.0;

    for(int i = 0; i < n; i++) {

        sum+=d[i];

    }
    return sum;
}

//Ceiling Function
int ceiling(int vector_dimension, int chunk_size) {

    int chunk_number;

    if (vector_dimension % chunk_size != 0) {
                
        chunk_number = vector_dimension / chunk_size + 1;
    
    } else {

        chunk_number = vector_dimension / chunk_size;

    }

    return chunk_number;

}

//Chuncked Addition
void add_vector_chuncked(double *x, double *y, double *d_chunked, int vector_dimension, double a, int chunk_size, int chunk_number, double *chunk_sum_array) {
        
    for(int chunk_idx = 0; chunk_idx < chunk_number; chunk_idx++) {
        
        int current_start = chunk_idx * chunk_size;
        int current_end = min((chunk_idx + 1) * chunk_size, vector_dimension);
        
        

        for(int internal_idx = current_start; internal_idx < current_end; internal_idx++) {

            d_chunked[internal_idx] = a*x[internal_idx] + y[internal_idx];

            chunk_sum_array[chunk_idx] += d_chunked[internal_idx]; 

        }

        printf("%.f\n", chunk_sum_array[chunk_idx]);

    }


}

//Check equality
void check_equality(double* d, double* d_chuncked, int vector_dimension) {
    
    int i = 0;

    while (i < vector_dimension && d[i] == d_chuncked[i]) {
        i++;
    }

    if (i != vector_dimension) {
        
        printf("Unequal numbers detected at index: %d \n", i);
    
    } else {
        
        printf("d == d_checked \n");
    
    }
    
}


int main() {


    // Set chunck_size
    int chunk_size = 8;

    // Parse input parameters from .config file
    config_struct config;
    char file_path[] = "./daxpy_chunck.conf";

    configurator_parser(file_path, &config);

    // Open x, y input files
    FILE *file_x_vector_ptr = fopen(config.file_x_vector, "r");
    FILE *file_y_vector_ptr = fopen(config.file_y_vector, "r");

    // Check dimensions
    int x_dimension = get_vector_dimension(file_x_vector_ptr);
    int y_dimension = get_vector_dimension(file_y_vector_ptr);


    if (x_dimension == y_dimension) {

        printf("Vector dimension matches\n");
    }

    else {
        printf("Vector dimensions do not match\n");

        return 0;
    }

    // Allocate memory for x and y
    double *x = malloc(x_dimension*sizeof(double));
    double *y = malloc(y_dimension*sizeof(double));

    // Initialize x and y vector entries
    vector_builder(file_x_vector_ptr, x);
    vector_builder(file_y_vector_ptr, y);

    // Allocate d and d_chuncked vector
    double *d = malloc(x_dimension*sizeof(double));
    double *d_chuncked = malloc(x_dimension*sizeof(double));

    // Declare and initialize sum variable
    double sum = 0;

    // Calculate number of chuncks
    int chunk_number = ceiling(x_dimension, chunk_size);
    double *chunk_sum_array = calloc(chunk_number, sizeof(double));

    // Declare and initialize chunck_sum variable
    double chunk_sum = 0;

    // Add vectors directly
    add_vector(x, y, d, x_dimension, config.a);

    // Add chuncks of the vector
    add_vector_chuncked(x, y, d_chuncked, x_dimension, config.a, chunk_size, chunk_number, chunk_sum_array);

    // Check the equality between the d and d_chuncked vector entries
    check_equality(d, d_chuncked, x_dimension);

    // Sum vector entries 
    sum = sum_func(d, x_dimension);
    chunk_sum = sum_func(chunk_sum_array, chunk_number);

    // Check sum equality
    double tol = 1.0E-11;
    if(fabs(sum - chunk_sum) < tol) {
        printf("The two values are equal\n");
        printf("sum = %.7f \n", sum);
        printf("chunk_sum = %.7f \n", chunk_sum);
    } else {
        printf("The two values are  not equal\n");
        printf("sum = %.7f \n", sum);
        printf("chunk_sum = %.7f \n", chunk_sum);

    }

    // Free memory and close file
    free(x);
    free(y);
    free(d);
    free(d_chuncked);

    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);



}