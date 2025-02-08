
#include <stdio.h>

int main()
{
	char* a_strings[] = {"apple", "banana", "peach", "apricot"};
	
	for (int i = 0; i < sizeof(a_strings) / sizeof(a_strings[0]); ++i)
		printf("%s\n", *(a_strings + i));

	return 0;
}

