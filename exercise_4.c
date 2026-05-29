/*
This program will numerically compute the integral of

                  4/(1+x*x) 

from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

History: Written by Tim Mattson, 11/99.
*/
#include "omp.h"
#include <stdio.h>

static long num_steps = 100000000;
double step;

int main()
{
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;
    step = 1.0 / (double) num_steps;


    start_time = omp_get_wtime();
    #pragma omp parallel
    {
    #pragma omp single
    printf(" num_threads = %d\n",omp_get_num_threads());

    #pragma omp for reduction(+:sum) private(x)
        for (i = 1; i <= num_steps; i++) {
            x = (i - 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
            
        }
    }
    run_time = omp_get_wtime() - start_time;

    pi = step * sum;

    printf("pi is %f\n", pi);
    printf("Time it took: %f\n", run_time);

    return 0;
}