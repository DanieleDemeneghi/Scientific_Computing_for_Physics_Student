#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void matrix_multiplication(double *A, double *B, double *C, int N) {

    printf("Multiplying matrices...\n");
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){

                C[N*i + j] += A[N*i + k]*B[N*k + j];

            }
        }
    }

}

void check_value(double *C, double expected, double tolerance, int N) {
    
    int check = 1;

    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++)
            if (fabs(C[N*i + j] - expected) > tolerance){
            check = 0;
            break;
        }
    }

    if (check == 1) {
        printf("Correctly multiplied matrices o dimension (%zu, %zu)\n", N, N);
    }
    else {
        printf("Incorrectly multiplied matrices of dimension (%zu, %zu)\n", N, N);
    }

}

int main () {
   
    int N = 1E4;

    //Declare matrix values and expected result
    const double A_val = 3.0;
    const double B_val = 7.1;
    double expected = 21.3 * (double)N;

    //Allocate memory for linearized 2D arrays
    double *A = malloc(N*N*sizeof(double)); 
    double *B = malloc(N*N*sizeof(double)); 
    double *C = calloc(N*N, sizeof(double));

    //Fill arrays with values
    printf("Filling matrices with values...\n");
    for (int i = 0; i < N; i++) {        
        for (int j = 0; j < N; j++) {
            
            A[N*i + j] = A_val;
            B[N*i + j] = B_val;
         
        }
    }

    //Execute multiplication
    matrix_multiplication(A, B, C, N);

    //Check result
    double tolerance = 1.0E-11;
    check_value(C, expected, tolerance, N);

    free(A);
    free(B);
    free(C);



}