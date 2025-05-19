
#include <omp.h>
#include <stdio.h>

void fooprivate()
{
	int tmp = 7;
	
	#pragma omp parallel for private(tmp)
	for (int i = 0; i < 10; ++i)
	{
		tmp += i;
	}

	printf("tmp value is %d\n", tmp);
}

void foofirstprivate()
{
	int tmp = 7;
	
	#pragma omp parallel for firstprivate(tmp)
	for (int i = 0; i < 10; ++i)
	{
		tmp += i;
		printf("inside tmp value is %d\n", tmp);
	}

	printf("tmp value is %d\n", tmp);
}

void foolastprivate()
{
	int tmp = 7;
	
	#pragma omp parallel for lastprivate(tmp)
	for (int i = 0; i < 10; ++i)
	{
		tmp += i;
		printf("inside tmp value is %d\n", tmp);
	}

	printf("tmp value is %d\n", tmp);
}

void foofirstlastprivate()
{
	int tmp = 7;
	
	#pragma omp parallel for firstprivate(tmp) lastprivate(tmp)
	for (int i = 0; i < 10; ++i)
	{
		tmp += i;
		printf("inside tmp value is %d\n", tmp);
	}

	printf("tmp value is %d\n", tmp);
}

int main()
{
	//fooprivate();
	//foofirstprivate();
	//foolastprivate();
	foofirstlastprivate();
	return 0;
}

