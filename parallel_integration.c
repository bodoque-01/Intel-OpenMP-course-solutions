/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The program was parallelized using OpenMP

(1) A line to include omp.h -- the include file that 
contains OpenMP's function prototypes and constants.

(2) A pragma that tells OpenMP to create a team of threads


(3) A pragma to split up loop iterations among the team
of threads.  This pragma includes 2 clauses to (1) create a 
private variable and (2) to cause the threads to compute their
sums locally and then combine their local sums into a 
single global value.

*/


#include "omp.h"
#include <stdio.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 4

int main() {
    double pi = 0.0;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int actual_num_threads = omp_get_num_threads();
        double sum = 0.0;
        for (int i = thread_id * (num_steps/actual_num_threads); i < (thread_id + 1) *(num_steps/actual_num_threads); i++) {
            double x = (i + 0.5) * step;
            sum += (4.0/(1.0 + x*x)) * step;
        }
        #pragma omp atomic
        pi += sum;
    }
    printf("Result: %f\n", pi);
    return 0;
}