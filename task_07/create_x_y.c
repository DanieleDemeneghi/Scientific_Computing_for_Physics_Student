#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_file(int N) {
    
    // Create filenames

    char file_x_vector_name[100];    
    char file_y_vector_name[100];
    char prefix[] = "./outputdir/vector_N";
    
    snprintf(file_x_vector_name, sizeof(file_x_vector_name), "%s_%d_y.dat", prefix, N);
    snprintf(file_y_vector_name, sizeof(file_y_vector_name), "%s_%d_x.dat", prefix, N);
    
    // Create files
    FILE *file_x_vector_ptr;
    FILE *file_y_vector_ptr;

    file_x_vector_ptr= fopen(file_x_vector_name, "w");
    file_y_vector_ptr= fopen(file_y_vector_name, "w"); 

    // Write to files
    double x_val = 0.1;
    double y_val = 7.1;

    for (int i = 0; i < N; i++) {

        fprintf(file_x_vector_ptr, "%.10f\n", x_val);
        fprintf(file_y_vector_ptr, "%.10f\n", y_val);

    }

    fclose(file_x_vector_ptr);
    fclose(file_y_vector_ptr);

}

int main() {
    int N = 100;
    create_file(N);
}