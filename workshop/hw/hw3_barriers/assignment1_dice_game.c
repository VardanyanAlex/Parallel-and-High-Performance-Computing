
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_barrier_t barrier;

#define PLAYER_NUM 4
#define ROUNDS_NUM 7

int player_score[PLAYER_NUM];


void* play_dice(void* args) {
	int* player_id = (int*)args;
	int current_round = 0;

	while (current_round < ROUNDS_NUM) {
		int rolled_number = rand() % 6 + 1;
        	player_score[*player_id] = player_score[*player_id] + rolled_number;
		printf("Player %d rolled %d \n", *player_id, rolled_number);
 		//sleep(1);
		++current_round;
        	pthread_barrier_wait(&barrier);
        	//printf("Round #%d was ended \n", current_round++);
    	}
}

int main(int argc, char *argv[]) {
	pthread_t th[PLAYER_NUM];
	srand(time(0));

	// scores init
	for (int i = 0; i < PLAYER_NUM; i++) 
		player_score[i] = 0;

    	pthread_barrier_init(&barrier, NULL, PLAYER_NUM);
	
	int i = 0;
	int player_ids[PLAYER_NUM];
	for (i = 0; i < PLAYER_NUM; i++) {
		player_ids[i] = i;
		if (pthread_create(&th[i], NULL, &play_dice, &player_ids[i]) != 0) {
			perror("Failed to create thread");
		}
	}

	for (int j = 0; j < PLAYER_NUM; j++) {
		if (pthread_join(th[j], NULL) != 0) {
			perror("Failed to join thread");
		}
	}
    	
	int winner_id = 0, winner_score = player_score[0];
	for (i = 1; i < PLAYER_NUM; i++){
		printf("%d \n", player_score[i]);
		if (player_score[i] > winner_score){
			winner_id = i;
			winner_score = player_score[i];
		}
	}
	
	printf("Player %d have won with score %d\n", winner_id, winner_score);

	pthread_barrier_destroy(&barrier);
	return 0;
}

