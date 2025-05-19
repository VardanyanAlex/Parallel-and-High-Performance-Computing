
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_STEPS 100

int main()
{
        double pi, sum[NUM_STEPS];
        double step = 1 / (double) NUM_STEPS;
        double start_time = omp_get_wtime();

        //for(int i = 1; i <= NUM_STEPS; ++i)
        //{

	omp_set_num_threads(NUM_STEPS);
	#pragma omp parallel 
	{
		int id = omp_get_thread_num();
                double x = (id + 1 - 0.5) * step;
                sum[id] = 4.0/(1.0 + x * x);
        }

	double total_sum = 0;
	for(int i = 0; i < NUM_STEPS; ++i)
		total_sum += sum[i];

        pi = step * total_sum;
        printf("pi = %f\n",pi);

        return 0;
}
