
#include <omp.h>
#include <stdio.h>
#include <unistd.h>

int recursive_fibonacci(int num)
{
	if (num == 0 || num == 1)
		return num;
	else
		return recursive_fibonacci(num - 1) + recursive_fibonacci(num - 2);
}

int omp_recursive_fibonacci_helper(int num)
{
	if (num <= 10)
	{
		//printf("Base case reached\n");
		//sleep(2);
		int f1 = 0, f2 = 0, result = 1;
		for (int i = 1; i < num; ++i)
		{
			f1 = f2;
			f2 = result;
			result = f1 + f2;
		}
		return result;
	}
	else
	{
		int num1;
		int num2;

		#pragma omp parallel shared(num1) shared(num2)
		{
			#pragma omp single
			{
				#pragma omp task
					num1 = omp_recursive_fibonacci_helper(num - 1);
				
				#pragma omp task
					num2 = omp_recursive_fibonacci_helper(num - 2);				
				
			}

			#pragma omp taskwait
			//printf("Thread #%d: num1=%d | num2=%d \n", omp_get_thread_num(), num1, num2);
		}
		
		//printf("Thread #%d: num1=%d | num2=%d \n", omp_get_thread_num(), num1, num2);
		return num1 + num2;
	}
}

int omp_recursive_fibonacci(int num)
{
	omp_set_num_threads(8);
	return omp_recursive_fibonacci_helper(num);
}

int main()
{
	int num;
	double start_time, end_time;

	printf("Enter the number: num = ");
	scanf("%d", &num);
	
	start_time = omp_get_wtime();
	int result = recursive_fibonacci(num);
	end_time = omp_get_wtime();
	printf("Naive recursive fibonacci result is: %d\n", result);
	printf("Executed in %f seconds\n", end_time - start_time);
	
	printf("\n\n-----------------------------------\n\n");
	
	start_time = omp_get_wtime();
	result = omp_recursive_fibonacci(num);
	end_time = omp_get_wtime();
	
	printf("Executed in %f seconds\n", end_time - start_time);
	printf("OMP recursive fibonacci result is: %d\n", result);
	
	return 0;
}

