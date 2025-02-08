
#include <stdio.h>

int main()
{
	int num = 7;
	int* p_num = &num;
	printf("%p\n", &num);
	printf("%p\n", p_num);

	*p_num = 8;
	printf("%d\n", *p_num);

	return 9;
}

