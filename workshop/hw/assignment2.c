
#include <stdio.h>

int main()
{
	int arr[5];
	for (int i = 0; i < 5; ++i)
		arr[i] = i;
	
	int* p_num = &arr[0];
	for (int i = 0; i < 5; ++i)
	{
		printf("%d\n", *p_num);
		++p_num;
	}

	p_num = &arr[0];

	for (int i = 0; i < 5; ++i)
		*(p_num + i) = *(p_num + i) + 10;

	for (int i = 0; i < 5; ++i)
		printf("%d %d\n", *(p_num+i), arr[i]);

	return 9;
}

