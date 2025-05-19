
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

struct node
{
	int value;
	struct node* next;
};

void init_list(struct node* head, int size)
{
	struct node* current = head;
	for (int i = 0; i < size; ++i)
	{
		struct node* next_node = malloc(sizeof(struct node));
		next_node->value = rand() % 10;
		current->next = next_node;
		current = next_node;
	}
}

int main()
{
	struct node* head = NULL;
	head = malloc(sizeof(struct node));
	head->value = rand() % 10;
	init_list(head, SIZE);


	struct node* arr[SIZE];
	struct node* current = head;
	for (int i = 0; i < SIZE; ++i)
	{
		printf("elem value:%d\n", current->value);
		arr[i] = current;
		current = current->next;
	}
	
	printf("parallel traversal________________\n");

	#pragma omp parallel for
	for (int i = 0; i < SIZE; ++i)
	{
		printf("Thred id: %d, elem value: %d\n", omp_get_thread_num(), arr[i]->value);
	}

	printf("parallel traversal________________\n");

	#pragma omp parallel
	{
	
	}

	return 0;
}

