
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define PLAYER_COUNT 5
#define ROUND_COUNT 6


int main()
{
	
	int rolled_numbers[PLAYER_COUNT];
        int current_round = 0;
	srand(time(0));
		while (current_round < ROUND_COUNT)
		{
			#pragma omp parallel num_threads(PLAYER_COUNT)
        		{
				int id = omp_get_thread_num();
				int rolled_number = rand() % 6 + 1;
				rolled_numbers[id] = rolled_number;
				
				#pragma omp barrier
				
				#pragma omp single
				{
					int max = rolled_numbers[0];
					int winner_id = 0;
					for (int i = 1; i < PLAYER_COUNT; ++i)
					{
						if(rolled_numbers[i] > max)
						{
							max = rolled_numbers[i];
							winner_id = i;
						}
					}

					printf("the winner is player %d wirth score %d\n", winner_id, max);
				}
			}
			++current_round;
		}

        return 0;
}

