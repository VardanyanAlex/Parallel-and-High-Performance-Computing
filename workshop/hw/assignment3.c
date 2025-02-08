
#include<stdio.h>

void swap(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int main()
{
	int x = 1;
	int y = 2;
	printf("before: %d %d\n", x, y);
	swap(&x, &y);
	printf("after: %d %d\n", x, y);

	return 0;
}

