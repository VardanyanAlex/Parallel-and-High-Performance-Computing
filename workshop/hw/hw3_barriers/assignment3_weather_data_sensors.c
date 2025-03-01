
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define SENSORS_NUM 5

pthread_barrier_t barrier;
int current_temperature[SENSORS_NUM];

void* detect_temperature(void* args) {
        int sensor_id = *((int*)(args));
	while(true){
       		 pthread_barrier_wait(&barrier);
       		 current_temperature[sensor_id] = rand() % 20 + 10;
       		 printf("Sensor %d detected temperature %d \n", sensor_id, current_temperature[sensor_id]);
       		 sleep(2);
       		 pthread_barrier_wait(&barrier);
       		 if (sensor_id == 0){
			int avg_temp = 0;
			for (int i = 0; i < SENSORS_NUM; ++i)
				avg_temp += current_temperature[i];

			avg_temp /= SENSORS_NUM;
			printf("The average temperature is %d\n", avg_temp);
		}
	}
}

int main(int argc, char *argv[]) {
        pthread_t th[SENSORS_NUM];
        srand(time(0));

        pthread_barrier_init(&barrier, NULL, SENSORS_NUM);

        int sensor_ids[SENSORS_NUM];
        for (int i = 0; i < SENSORS_NUM; i++) {
                sensor_ids[i] = i;
                if (pthread_create(&th[i], NULL, &detect_temperature, &sensor_ids[i]) != 0) {
                        perror("Failed to create thread");
                }
        }

        for (int j = 0; j < SENSORS_NUM; j++) {
                if (pthread_join(th[j], NULL) != 0) {
                        perror("Failed to join thread");
                }
        }

        pthread_barrier_destroy(&barrier);
        return 0;
}

