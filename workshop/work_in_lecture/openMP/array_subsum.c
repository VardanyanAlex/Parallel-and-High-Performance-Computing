
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SUM_ARR_SIZE 2
#define ARR_SIZE 100

int arr[ARR_SIZE];
double sum[SUM_ARR_SIZE];

struct Indices
{
        int first_index;
        int last_index;
	int id_in_arr;
};

void* sum_arr(void* arg)
{
        struct Indices* ids = (struct Indices*)arg;
        for (int i = ids->first_index; i <= ids->last_index; ++i)
                sum[ids->id_in_arr] += arr[i];

        return NULL;
}

int main()
{
        for (int i = 0; i < SUM_ARR_SIZE; ++i)
                sum[i] = 0;

	for (int i = 1; i < ARR_SIZE + 1; ++i)
		arr[i] = i;

        clock_t begin = clock();

        pthread_t thread1, thread2;

        struct Indices ids1 = {0, 50, 0};
        if (pthread_create(&thread1, NULL, sum_arr, (void*)&ids1))
        {
                perror("failed to create thread 1");
                return -1;
        }

        struct Indices ids2 = {51, 100, 1};
        if (pthread_create(&thread2, NULL, sum_arr, (void*)&ids2))
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

        double final_sum = 0;
        for (int i = 0; i < SUM_ARR_SIZE; ++i)
                final_sum += sum[i];

        printf("%f\n", final_sum);

        clock_t end = clock();
        printf("Time spent: %f\n", (double)(end - begin));

        return 0;
}

