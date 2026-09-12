#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_vector.h>

double vec[] = {1.0, 1e16, -1e16, -0.5};

double kahan_func_sum(double *vec) {
    
    double sum = 0.0;
    double c = 0.0;

    for(int i = 0; i < 4; i++) {
        double y = vec[i] - c;
        double t = sum + y;
        c = (t - sum )- y;
        sum = t;

    }
    
    return sum;
}

int main() {

    // For loop summation
    double for_loop_sum = 0; 
    
    for(int i = 0; i < 4; i++) {
        for_loop_sum += vec[i];
    }

    //gsl_vector_sum
    //Initialize vector elements
    gsl_vector *gsl_vec = gsl_vector_alloc(4);

    double gsl_sum;
    
    for(int i = 0; i < 4; i++) {
        gsl_vector_set(gsl_vec, i, vec[i]);
    }

    gsl_sum = gsl_vector_sum(gsl_vec);


    //Kahan summation
    double kahan_sum = kahan_func_sum(vec);

    printf("For loop summation yields: %17g\n", for_loop_sum);
    printf("GSL vector summation yields: %17g\n", gsl_sum);
    printf("Kahan algorithm summation yields: %17g\n", kahan_sum);

    gsl_vector_free(gsl_vec);

    return 0;

}

