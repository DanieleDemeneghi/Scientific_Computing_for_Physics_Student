#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"
#include "parser.h"    

// Define structure to hold configuration data
typedef struct  {
    char file_vector_name[100];
    double a;
} config_struct;

// Parse configuration file data
int configurator_parser(char *file_path, config_struct *config) {
    
    config_option_t co;
    
    if ((co = read_config_file(file_path)) == NULL) {
        perror("read_config_file()");
        return -1;
    }
    while(co != NULL) {

        if (strcmp(co->key, "file_vector" ) == 0) {
            strcpy(config->file_vector_name, co->value);
        }

        else if (strcmp(co->key, "a") == 0) {
            config->a = atof(co->value);
       
        }

        co = co->prev;
    }

    return 0;

}

void read_add_write_file_vector(const char *file_vector_name_ptr, float a) {

    const char *dataset_name_x_ptr = "/x";
    const char *dataset_name_y_ptr = "/y";

    //Open hdf5 file
    hid_t file_vector = H5Fopen(file_vector_name_ptr, H5F_ACC_RDWR, H5P_DEFAULT);
    
    //Open datasets
    hid_t dataset_x = H5Dopen2(file_vector, dataset_name_x_ptr, H5P_DEFAULT);
    hid_t dataset_y = H5Dopen2(file_vector, dataset_name_y_ptr, H5P_DEFAULT);
    
    // Access dataspaces
    hid_t dataspace_x = H5Dget_space(dataset_x);
    hid_t dataspace_y = H5Dget_space(dataset_y);

    // Get dataspace dimension
    hsize_t x_dim[1];
    hsize_t y_dim[1]; 
    
    H5Sget_simple_extent_dims(dataspace_x, x_dim, NULL);
    H5Sget_simple_extent_dims(dataspace_y, y_dim, NULL);
   
    if (x_dim[0] == y_dim[0]) {
        int N = (int)x_dim[0];
        
        // Allocate vector memories
        double *x = malloc(N*sizeof(double));
        double *y = malloc(N*sizeof(double));
        double *d = malloc(N*sizeof(double));
        
        // Read content of dataset_x and dataset_y into x and y
        herr_t status_x_read = H5Dread (dataset_x, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, x);
        if (status_x_read < 0) {
            printf("Error reading x dataset\n");
        }
        herr_t status_y_read = H5Dread (dataset_y, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, y);
        if (status_y_read < 0) {
            printf("Error reading y dataset\n");
        }


        // Perform calculation
        for(int i = 0; i < N; i++) {
            
            d[i] = a*x[i] + y[i];
        
        }
        
        // Create dataspace and dataset for d
        hid_t dataspace_d = H5Screate_simple(1, x_dim, NULL);
        hid_t dataset_d = H5Dcreate1(file_vector, "/d", H5T_NATIVE_DOUBLE, dataspace_d, H5P_DEFAULT);
        herr_t status_d = H5Dwrite(dataset_d, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, d);
        if (status_d < 0) {
            printf("Error writing d dataset\n");
        }

        // Close dataset, dataspaces and file
        H5Dclose(dataset_x);
        H5Dclose(dataset_y);
        H5Sclose(dataspace_d);
        H5Dclose(dataset_d);
        H5Fclose(file_vector);

        // Free up memory
        free(x);
        free(y);
        free(d);
    
    } else {
            printf("Vector dimensions do not match: can't perform operation");
    };

}

int main() {
    
    config_struct config;
    char *file_path_ptr = "daxpy_hdf.conf";

    configurator_parser(file_path_ptr, &config);
    read_add_write_file_vector(config.file_vector_name, config.a);

    
}
