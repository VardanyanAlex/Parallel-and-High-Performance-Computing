
#include <stdio.h>

void f(int* p)
{
	(*p)++;
}

int main()
{
	int x = 5;
	printf("%p\n", &x);

	int* p = &x;
	printf("%p\n", p);

	*p = 7;
	printf("%d\n", *p);
	
	printf("%p\n", &p);

	
	printf("%d\n", x);
	f(&x);
	printf("%d\n", x);
}
