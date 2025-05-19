#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_STEPS 100

int main()
{
	double pi, sum = 0;
	double step = 1 / (double) NUM_STEPS, x;
	double start_time = omp_get_wtime();

	for(int i = 1; i <= NUM_STEPS; ++i)
	{
		x = (i - 0.5) * step;
		sum += 4.0/(1.0 + x * x);
	}

	pi = step * sum;
	printf("pi = %f\n",pi);

	return 0;
}
