
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define M_THREADS_NUM 7

pthread_barrier_t barrier;

void stage_one(int thread_id){
	printf("Thread #%d is working in stage 1\n", thread_id);
	sleep(5);
}

void stage_two(int thread_id){
	printf("Thread #%d is working in stage 2\n", thread_id);
	sleep(2);
}

void stage_three(int thread_id){
	printf("Thread #%d is working in stage 3\n", thread_id);
	sleep(7);
}

void* run_pipeline(void* args) {
	int thread_id = *((int*)(args));
	stage_one(thread_id);
        pthread_barrier_wait(&barrier);
        
	stage_two(thread_id);
        pthread_barrier_wait(&barrier);
	
	stage_three(thread_id);
	pthread_barrier_wait(&barrier);
	
	printf("The pipeline have run successfully!\n\n");
}

int main(int argc, char *argv[]) {
        pthread_t th[M_THREADS_NUM];
        srand(time(0));

        pthread_barrier_init(&barrier, NULL, M_THREADS_NUM);

        int thread_ids[M_THREADS_NUM];
        for (int i = 0; i < M_THREADS_NUM; i++) {
                thread_ids[i] = i;
                if (pthread_create(&th[i], NULL, &run_pipeline, &thread_ids[i]) != 0) {
                        perror("Failed to create thread");
                }
        }

        for (int j = 0; j < M_THREADS_NUM; j++) {
                if (pthread_join(th[j], NULL) != 0) {
                        perror("Failed to join thread");
                }
        }

        pthread_barrier_destroy(&barrier);
        return 0;
}

