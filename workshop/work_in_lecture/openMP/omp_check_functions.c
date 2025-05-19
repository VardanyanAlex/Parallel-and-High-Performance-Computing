
#include <stdio.h>
#include <omp.h>

int main()
{
	omp_set_num_threads(1000);

	printf("Number of threads:%d\n", omp_get_num_threads());

	#pragma omp parallel
	{
		printf("Number of threads:%d\n", omp_get_num_threads());
	}
	
	printf("Number of threads:%d\n", omp_get_num_threads());
	
	return 0;
}

