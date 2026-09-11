#include <stdio.h>
#include <stdlib.h>
#include "hdf5.h"    
    
void create_file(int N) {

    double x_val = 0.1;
    double y_val = 7.1;
    
    // Create vectors
    double *x = malloc(N*sizeof(double));
    double *y = malloc(N*sizeof(double));

    for(int i = 0; i < N; i++) {
        x[i] = x_val;
        y[i] = y_val;
    };

    // Create HDF5 file
    hid_t file_vector;
    hid_t dataspace_x;
    hid_t dataspace_y;
    hid_t dataset_x;
    hid_t dataset_y;
    herr_t status_x;
    herr_t status_y;

    file_vector = H5Fcreate("./filevector.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    hsize_t dims[1] = {N};

    dataspace_x = H5Screate_simple(1, dims, NULL);
    dataspace_y = H5Screate_simple(1, dims, NULL);

    dataset_x = H5Dcreate1(file_vector, "/x", H5T_NATIVE_DOUBLE, dataspace_x, H5P_DEFAULT);
    dataset_y = H5Dcreate1(file_vector, "/y", H5T_NATIVE_DOUBLE, dataspace_y, H5P_DEFAULT);

    // Write to files
    status_x = H5Dwrite(dataset_x, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, x);
    if (status_x < 0) {
            printf("Error writing x dataset\n");
    }
    status_y = H5Dwrite(dataset_y, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, y);
    if (status_y < 0) {
            printf("Error writing y dataset\n");
    }


    // Close datasets and dataspaces and file
    H5Dclose(dataset_x);
    H5Dclose(dataset_y);
    H5Sclose(dataspace_x);
    H5Sclose(dataspace_y);
    H5Fclose(file_vector);

    // Free vector memory
    free(x);
    free(y);

}

int main(){
    create_file(100);

}