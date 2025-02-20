
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t lock;
double sum = 0;
double x = 10;

struct Indices
{
	int first_index;
	int last_index;
};

double factorial(int n)
{
	double fact = 1;
	for (int i = 1; i <= n; ++i)
		fact *= i;

	return fact;
}

void* taylor_sum_sin(void* arg)
{
	pthread_mutex_lock(&lock);
	struct Indices* ids = (struct Indices*)arg;
	for (int i = ids->first_index; i <= ids->last_index; ++i)
		sum += pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
	
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main()
{
	clock_t begin = clock();

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		perror("\nmutex init has failed\n");
		return -1;
	}

	pthread_t thread1, thread2;

	struct Indices ids1 = {0, 50};
	if (pthread_create(&thread1, NULL, taylor_sum_sin, (void*)&ids1))
	{
		perror("failed to create thread 1");
		return -1;
	}
	
	struct Indices ids2 = {51,100};
	if (pthread_create(&thread2, NULL, taylor_sum_sin, (void*)&ids2))
	{
		perror("failed to create thread 2");
		return -1;
	}

	if (pthread_join(thread1, NULL) != 0)
	{
		perror("failed to join thread 1");
		return -1;
	}

	if (pthread_join(thread2, NULL) != 0)
	{
		perror("failed to join thread 2");
		return -1;
	}

	pthread_mutex_destroy(&lock);

	printf("%f\n", sum);

	clock_t end = clock();
	printf("Time spent: %f\n", (double)(end - begin));

	return 0;
}

