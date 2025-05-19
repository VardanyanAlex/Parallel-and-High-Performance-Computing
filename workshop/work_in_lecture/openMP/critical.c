
#include <stdio.h>
#include <omp.h>

int main()
{
	int count = 0;
	#pragma omp parallel num_threads(4)
        {
		#pragma omp critical
		{
			++count;
			printf("Thread %d: count = %d\n", omp_get_thread_num(), count);
		}

                //printf("Thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
        }
        return 0;
}

