
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* p_num = (int*)malloc(sizeof(int));
	if (p_num == NULL)
	{
		printf("Couldn't allocate memory!\n");
		return -1;
	}

	*p_num = 77;
	printf("%d\n", *p_num);

	int* p_arr = (int*)malloc(sizeof(int) * 5);
	if (p_arr == NULL)
	{
		printf("Couldn't allocate memory for the array\n");
		return -1;
	}
	
	for (int i = 0; i < 5; ++i)
	{
		*(p_arr + i) = i;
		printf("%d\n", *(p_arr + i));
	}

	free(p_num);
	free(p_arr);

	return 0;
}

