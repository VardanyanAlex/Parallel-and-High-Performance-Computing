
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_barrier_t barrier;

#define PLAYER_NUM 4

void* play_game(void* args) {
	int player_id = *((int*)(args));
        int preparing_time = rand() % 5 + 1;
        printf("Player %d is getting ready, this might take %d seconds \n", player_id, preparing_time);
        sleep(preparing_time);
        pthread_barrier_wait(&barrier);
        printf("Game Started! \n");
}

int main(int argc, char *argv[]) {
        pthread_t th[PLAYER_NUM];
        srand(time(0));

        pthread_barrier_init(&barrier, NULL, PLAYER_NUM);

        int i = 0;
        int player_ids[PLAYER_NUM];
        for (i = 0; i < PLAYER_NUM; i++) {
                player_ids[i] = i;
                if (pthread_create(&th[i], NULL, &play_game, &player_ids[i]) != 0) {
                        perror("Failed to create thread");
                }
        }

        for (int j = 0; j < PLAYER_NUM; j++) {
                if (pthread_join(th[j], NULL) != 0) {
                        perror("Failed to join thread");
                }
        }
	
	pthread_barrier_destroy(&barrier);
        return 0;
}

