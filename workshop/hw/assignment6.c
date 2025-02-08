
#include <stdio.h>

int str_length(char* p_str)
{
	int n_length = 0;
	while(*(p_str++) != '\0')
		++n_length;
	
	return n_length;
}

int main()
{
	char const* p_str = "string_literal";
	for (char const* p_char = p_str; *p_char != '\0'; ++p_char)
		printf("%c ", *p_char);
	
	printf("\n");

	printf("length of word 'apple' is: %d\n", str_length("apple"));

	return 0;
}

