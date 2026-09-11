#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void vector_addition(double *x, double *y, double *d, int N) {
    
    const double a = 3.0;
    const double expected = 7.4;

    // Add vectors
    for (int i = 0; i < N; i++) {
        
        d[i] = a * x[i] + y[i];
     
    }


}

void check_value(double *d, double expected, double tolerance, int N) {
    
    int check = 1;

    for (int i = 0; i < N; i++) {

        if (fabs(d[i] - expected) > tolerance){
            check = 0;
            break;
        }
    }

    if (check == 1) {
        printf("Correctly added vectors of dimension (%zu, 1)\n", N);
    }
    else {
        printf("Incorrectly added vectors of dimension (%zu, 1)\n", N);
    }

    
}

int main () {
    
    // Number of vector elements
    int N = 1E8;

    // x and y vector elements value
    const double x_val = 0.1;
    const double y_val = 7.1;

    // Allocate memory for the three vectors
    double *x = malloc(N * sizeof(double));
    double *y = malloc(N * sizeof(double));
    double *d = malloc(N * sizeof(double));

    // Initialize x and y vector elements
    for (int i = 0; i < N; i++) {
        
        x[i] = x_val;
        y[i] = y_val;
    
    }

    // Add vectors
    vector_addition(x, y, d, N);

    // Check result value
    const double expected = 7.4;
    double tolerance = 1E-15; 
    check_value(d, expected, tolerance, N);


    free(x);
    free(y);
    free(d);



}