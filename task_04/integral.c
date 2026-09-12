#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

const int N = 100;
const double x_min = 0;
const double x_max = PI/2;


double integral_calculator(int N) {

    double dx = (x_max - x_min)/N;

    
    // Assign filename
    char filename[100];
    char prefix[] = "./Function";
    snprintf(filename, sizeof(filename), "%s_%d.dat",prefix, N);
    
    // Allocate memory for file, x and f
    FILE *fptr = fopen(filename, "w");

    fprintf(fptr, "x f(x)\n");
    
    double *x = malloc((N+1)*sizeof(double));
    double *f = malloc((N+1)*sizeof(double));
    double result_integral = 0;
        
    // Calculate function and print to file
    for(int i = 0; i < N + 1; i++) {

        x[i] = i*dx;

        f[i] = exp(x[i])*cos(x[i]);

        fprintf(fptr, "%.17f %.17f \n", x[i], f[i]);


    }

    // Calculate area using trapezoid rule
    for(int i = 0; i < N; i++) {
        
        result_integral = result_integral + dx*(f[i + 1] + f[i])/2;

    }

    double exact_integral = (exp(x_max) - 1)*0.5;
    double epsrel = result_integral/exact_integral - 1;

    printf("Integral result using trapezoid method is : %.16f using N %d intervals\n", result_integral, N);
    printf("Exact value is : %.16f\n", exact_integral);
    printf("Relative error for using  N %i intervals is : %.16f\n", N, epsrel);
    printf("-------------------------------------------------------------------------\n");

    
    free(x);
    free(f);
    fclose(fptr);

    return epsrel;
    
}

int main() {
    
    int i = 1;
    double previous_epsrel = integral_calculator(pow(10, i));
    double epsrel = integral_calculator(pow(10, i + 1));

    while (epsrel - previous_epsrel > 0 ) {
        
        i  = i + 1;
        previous_epsrel = epsrel;
        epsrel = integral_calculator(pow(10, i + 1));


    }

    printf("Lowest relative error reached is: %.20f at 10^%d intervals", epsrel, i);

    return 0;
}