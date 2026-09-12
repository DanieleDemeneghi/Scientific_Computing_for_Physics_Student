#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gsl/gsl_rng.h"
#include "gsl/gsl_randist.h"
#include "gsl/gsl_statistics_double.h"
#include <fftw3.h>

void calculate_errors(double *X, double *Y, int N) {


    // Declare variables and allocate error matrices
    double mean_absolute_error = 0;
    double median_absolute_error = 0;

    double mean_relative_error;
    double median_relative_error;

    double *absolute_error = malloc(N*N*sizeof(double));
    double *relative_error = malloc(N*N*sizeof(double));


    // Calculate error matrices 
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            int idx = N*i + j;

            absolute_error[idx] = X[idx] - Y[idx];
            
            if(Y[idx] != 0.0) {
                relative_error[idx] = absolute_error[idx]/Y[idx];
            } else {
                relative_error[idx];
            }
            

            absolute_error[idx] = absolute_error[idx]*absolute_error[idx];
            relative_error[idx] = relative_error[idx]*relative_error[idx];

        }
    }

    //Calculate mean and median of error matrices
    mean_absolute_error = sqrt(gsl_stats_mean(absolute_error, 1, N*N));
    mean_relative_error = sqrt(gsl_stats_mean(relative_error, 1, N*N));

    median_absolute_error = sqrt(gsl_stats_median(absolute_error, 1, N*N));
    median_relative_error = sqrt(gsl_stats_median(relative_error, 1, N*N));

    // Print results on terminal
    printf("Mean absolute error: %.20f\n", mean_absolute_error);
    printf("Median absolute error: %.20f\n", median_absolute_error);
    printf("Mean relative error: %.20f\n", mean_relative_error);
    printf("Median relative error: %.20f\n", median_relative_error);

    // Free memory
    free(absolute_error);
    free(relative_error);

}

void task(int N) {
    
    //Allocate input and output matrices
    double *A;
    double *A_c2c_rec_real;
    double *A_r2c_rec_real;
    
    fftw_complex *A_complex;
    fftw_complex *A_c2c_rec;
    
    fftw_complex *C;
    fftw_complex *R;


    A = (double*) fftw_alloc_real(N*N*sizeof(double));
    A_c2c_rec_real = (double*) fftw_alloc_real(N*N*sizeof(double));
    A_r2c_rec_real = (double*) fftw_alloc_real(N*N*sizeof(double));

    A_c2c_rec = (fftw_complex*) fftw_malloc(N*N*sizeof(fftw_complex));
    A_complex = (fftw_complex*) fftw_malloc(N*N*sizeof(fftw_complex));
    
    C = (fftw_complex*) fftw_malloc(N*N*sizeof(fftw_complex));
    R = (fftw_complex*) fftw_malloc(N*(N/2 +1)*sizeof(fftw_complex));    


    //Set up random number generator
    const gsl_rng_type *T;
    gsl_rng *r;
    
    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, 12345);


    //Initialize A and A_complex matrix values
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            A[N*i + j] = 1 + gsl_ran_gaussian(r, 1.0);
            A_complex[N*i + j][0] = A[N*i + j];
            A_complex[N*i + j][1] = 0.0;
        
        }
            
    }

    //Set up and execute c2c FFTW plan
    fftw_plan plan_c2c;
    plan_c2c = fftw_plan_dft_2d(N, N, A_complex, C, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan_c2c);

    //Reconstruct A matrix with  inverse c2c FFTW
    fftw_plan plan_c2c_rec;
    plan_c2c_rec = fftw_plan_dft_2d(N, N, C, A_c2c_rec, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan_c2c_rec);

    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

        A_c2c_rec_real[N*i + j] = A_c2c_rec[N*i + j][0]/(N*N); 
    
        }
    }

    //Calculate errors
    printf("Errors of c2c FFTW\n");
    calculate_errors(A_c2c_rec_real, A, N);
    printf("-------------------\n");

    //Set up and execute r2c FFTW plan
    fftw_plan plan_r2c;
    plan_r2c = fftw_plan_dft_r2c_2d(N, N, A, R, FFTW_ESTIMATE);
    fftw_execute(plan_r2c);

        
    //Reconstruct A matrix with c2r FFTW
    fftw_plan plan_c2r_rec;
    plan_c2r_rec = fftw_plan_dft_c2r_2d(N, N, R, A_r2c_rec_real, FFTW_ESTIMATE);
    fftw_execute(plan_c2r_rec);

    //Rinormalize
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

        A_r2c_rec_real[N*i + j] = A_r2c_rec_real[N*i + j]/(N*N); 
    
        }
    }


    
    //Calculate errors
    printf("Errors of r2c FFTW\n");
    calculate_errors(A_r2c_rec_real, A, N);
    printf("-------------------\n");

    printf("C[0, 0] == %.17f + %.17fi\n", C[0][0], C[0][1]);
    printf("R[0, 0] == %.17f + %.17fi\n", R[0][0], R[0][1]);
    printf("-------------------\n");

    //Destroy plans and free up memory
    fftw_destroy_plan(plan_c2c);
    fftw_destroy_plan(plan_c2c_rec);
    fftw_destroy_plan(plan_r2c);
    fftw_destroy_plan(plan_c2r_rec);

        
    fftw_free(A);
    fftw_free(A_c2c_rec_real);
    fftw_free(A_r2c_rec_real);
    
    fftw_free(A_complex);
    fftw_free(A_c2c_rec);
    
    fftw_free(C);
    fftw_free(R);


}  

void bonus_task(int N) {
    
    //Allocate input and output matrices
    double *A;

    double *C_direct_real;
    double *C_direct_imaginary;
    double *C_from_R_real;
    double *C_from_R_imaginary;
         
    fftw_complex *A_complex;    
    
    fftw_complex *C_direct;
    fftw_complex *C_from_R;
    
    fftw_complex *R;


    A = (double*) fftw_alloc_real(N*N*sizeof(double));
    C_direct_real = (double*) fftw_alloc_real(N*N*sizeof(double));
    C_direct_imaginary = (double*) fftw_alloc_real(N*N*sizeof(double));

    C_from_R_real = (double*) fftw_alloc_real(N*N*sizeof(double));
    C_from_R_imaginary = (double*) fftw_alloc_real(N*N*sizeof(double));

    A_complex = (fftw_complex*) fftw_malloc(N*N*sizeof(fftw_complex));
    
    C_direct = (fftw_complex*) fftw_malloc(N*N*sizeof(fftw_complex));
    C_from_R = (fftw_complex*) fftw_malloc(N*N*sizeof(fftw_complex));
    R = (fftw_complex*) fftw_malloc(N*(N/2 +1)*sizeof(fftw_complex));    


    //Set up random number generator
    const gsl_rng_type *T;
    gsl_rng *r;
    
    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, 12345);


    //Initialize A and A_complex matrix values
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            A[N*i + j] = 1 + gsl_ran_gaussian(r, 1.0);
            A_complex[N*i + j][0] = A[N*i + j];
            A_complex[N*i + j][1] = 0.0;
        
        }
            
    }

    //Set up and execute c2c FFTW plan
    fftw_plan plan_c2c;
    plan_c2c = fftw_plan_dft_2d(N, N, A_complex, C_direct, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan_c2c);

    //Copy real and imaginary parts of C_direct in C_direct_real and C_direct_imaginary complex
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            C_direct_real[N*i + j] = C_direct[N*i + j][0];
            C_direct_imaginary[N*i + j] = C_direct[N*i + j][1];
        
        }
            
    }


    //Set up and execute r2c FFTW plan
    fftw_plan plan_r2c;
    plan_r2c = fftw_plan_dft_r2c_2d(N, N, A, R, FFTW_ESTIMATE);
    fftw_execute(plan_r2c);

    //Reconstruct C from R
    for (int kx = 0; kx < N; kx++) {
        for (int ky = 0; ky <= N / 2; ky++) {

            C_from_R[kx * N + ky][0] = R[kx * (N / 2 + 1) + ky][0];
            C_from_R[kx * N + ky][1] = R[kx * (N / 2 + 1) + ky][1];

            C_from_R_real[kx * N + ky] = C_from_R[kx * N + ky][0];
            C_from_R_imaginary[kx * N + ky] = C_from_R[kx * N + ky][1];

        }

        for (int ky = N/2 + 1; ky < N; ky++) {

            int kx_sym = (N - kx) % N;
            int ky_sym = N - ky;

            C_from_R[kx * N + ky][0] = R[kx_sym * (N/ 2 + 1) + ky_sym][0];
            C_from_R[kx * N + ky][1] = -R[kx_sym * (N/ 2 + 1) + ky_sym][1];

            C_from_R_real[kx * N + ky] = C_from_R[kx * N + ky][0];
            C_from_R_imaginary[kx * N + ky] = C_from_R[kx * N + ky][1];

        }
    }

    //Check equality between C_direct and C_from_R
    printf("Bonus task\n");
    printf("Real part comparison\n");
    calculate_errors(C_direct_real, C_from_R_real, N);
    printf("-------------------\n");
    printf("Imaginary part comparison\n");
    calculate_errors(C_direct_imaginary, C_from_R_imaginary, N);
    printf("-------------------\n");

    //Destroy plans and free up memory
    fftw_destroy_plan(plan_c2c);
    fftw_destroy_plan(plan_r2c);
        
    fftw_free(A);    
    fftw_free(A_complex);
    
    fftw_free(C_direct);
    fftw_free(C_from_R);
    fftw_free(R);



}  


int main() {
    
    task(1000);
    bonus_task(6);
    
}