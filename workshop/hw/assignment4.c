
#include <stdio.h>

int main()
{
	int x = 77;
	int* p_x = &x;
	int** pp_x = &p_x;
	printf("%d\n%d\n", *p_x, **pp_x);

	return 0;
}

