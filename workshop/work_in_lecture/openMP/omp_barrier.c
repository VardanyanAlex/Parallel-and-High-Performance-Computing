
#include <omp.h>
#include <stdio.h>

int main()
{
	#pragma omp parallel
	{
		int id = omp_get_thread_num();

		#pragma omp for nowait
		for (int i = 0; i < 4; ++i)
			printf("Thread %d is processing iteration %d\n", id, i);

		//#pragma omp barrier

		printf("Thread %d reached after loop\n", id);
	}


	return 0;
}

