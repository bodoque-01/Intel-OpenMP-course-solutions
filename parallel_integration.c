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