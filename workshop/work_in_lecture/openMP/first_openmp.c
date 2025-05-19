
#include <stdio.h>
#include <omp.h>

int main()
{
	int num_threads;

	printf("Enter the number of threads: ");
	scanf("%d", &num_threads);
	//omp_set_num_threads(num_threads);

	#pragma omp parallel num_threads(num_threads)
	{
		int ID = omp_get_thread_num();
		printf("hello(%d)", ID);
		printf("world(%d)\n", ID);
	}
	return 0;
}

