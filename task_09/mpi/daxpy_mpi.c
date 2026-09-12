#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
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



// Main program
int main(int argc, char **argv) {

    int N = 1000000;

    int rank;
    int size;

    // Initialize MPI
    MPI_Init(&argc, &argv);   
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    // Check correct size initialization
    if (size > 4) {
        if (rank == 0) {
            printf("Error: use at most 4 MPI processes.\n");
        }

        MPI_Finalize();
        return 1;
    }

    config_struct config;
    char file_path[] = "./daxpy_mpi.conf";

    configurator_parser(file_path, &config);
    
    FILE *file_x_vector_ptr = fopen(config.file_x_vector, "r");
    FILE *file_y_vector_ptr = fopen(config.file_y_vector, "r");

    if(N % size != 0) {   

        printf("Error: can't divide N for size");
        MPI_Finalize();
        return 1; 
    
    }

    int N_loc = N/size;

    //Allocate memory for variables local to each mpi process
    double *x_loc = malloc(N_loc*sizeof(double));
    double *y_loc = malloc(N_loc*sizeof(double));
    double *d_loc = malloc(N_loc*sizeof(double));

    double *x = NULL;
    double *y = NULL;
    double *d_mpi = NULL;
    double *d_serial = NULL;

    
    if(rank == 0) {
        x = malloc(N*sizeof(double));
        y = malloc(N*sizeof(double));
        d_mpi = malloc(N * sizeof(double));
        d_serial = malloc(N*sizeof(double));

        vector_builder(file_x_vector_ptr, x);
        vector_builder(file_y_vector_ptr, y);

    }

    MPI_Scatter(x, N_loc, MPI_DOUBLE, x_loc, N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, N_loc, MPI_DOUBLE, y_loc, N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    double start_time_loc = MPI_Wtime();

    add_vector(x_loc, y_loc, d_loc, N_loc, config.a);
    
    MPI_Barrier(MPI_COMM_WORLD);

    double end_time_loc = MPI_Wtime();
    double run_time_loc = end_time_loc - start_time_loc;

    double run_time_mpi;

    MPI_Reduce(&run_time_loc, &run_time_mpi, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Gather(d_loc, N_loc, MPI_DOUBLE, d_mpi, N_loc, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    if (rank == 0) {

        double start_time_serial = MPI_Wtime();

        add_vector(x, y, d_serial, N, config.a);

        double end_time_serial = MPI_Wtime();
        double run_time_serial = end_time_serial - start_time_serial;

        printf("Serial execution: %.6f ms\n", run_time_serial * 1000);
        printf("MPI execution:    %.6f ms\n", run_time_mpi * 1000);

        fclose(file_x_vector_ptr);
        fclose(file_y_vector_ptr);
    }

    free(x_loc);
    free(y_loc);
    free(d_loc);

    if (rank == 0) {
        free(x);
        free(y);
        free(d_mpi);
        free(d_serial);
    }

    MPI_Finalize();

    return 0;
}