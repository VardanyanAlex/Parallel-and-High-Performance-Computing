
#include <immintrin.h> // For AVX2
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define SIZE 1000000

void to_upper(char* str)
{
    const char offset = 'a' - 'A';
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a'&& str[i] <= 'z')
            str[i] -= offset;
    }
}

void simd_to_upper(char* str)
{
	int len = strlen(str);
	int i = 0;
	for (; i <= len - 32; i += 32)
	{
		__m256i chunk = _mm256_loadu_si256((__m256i*)&str[i]);
		__m256i greater_a = _mm256_cmpgt_epi8(chunk, _mm256_set1_epi8('a' - 1));
		__m256i less_z = _mm256_cmpgt_epi8(_mm256_set1_epi8('z'), chunk);
		
		__m256i bool_res = _mm256_and_si256(greater_a, less_z);
		__m256i offsets = _mm256_and_si256(bool_res, _mm256_set1_epi8(32));
		__m256i upper = _mm256_sub_epi8(chunk, offsets);

		_mm256_storeu_si256((__m256i*)&str[i], upper);
	}
	
	const char offset = 'a' - 'A';
	for (;i < len; ++i)
		if (str[i] >= 'a'&& str[i] <= 'z')
			str[i] -= offset;

}

/*
int simd_max_search(int* arr)
{
    if (SIZE < 8)
        return naive_max_search(arr);

    //__m256 max_arr = _mm256_set1_epi32(INT_MIN);
    __m256i max_arr = _mm256_loadu_si256((const __m256i*)&arr[0]);

    int i = 8;
    for (; i <= SIZE - 8; i += 8) {
        __m256i current_chunk = _mm256_loadu_si256((const __m256i*)&arr[i]);
        max_arr = _mm256_max_epi32(max_arr, current_chunk);
    }

    int max_array[8];
    _mm256_storeu_si256((__m256i*)max_array, max_arr);

    int max = INT_MIN;
    for (int j = 0; j < 8; ++j)
        if (max_array[j] > max)
            max = max_array[j];

    for (i; i < SIZE; ++i)
        if (arr[i] > max)
            max = arr[i];

    return max;
}
*/

int main() {
    srand(time(NULL));
    char str1[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    char str2[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";

    // Initialize the array
    //for (int i = 0; i < SIZE; i++) {
    //    arr[i] = rand() % 100 + 1;
    //}

    clock_t start = clock();
    to_upper(str1);
    clock_t end = clock();
    printf("Naive approach | Result is:%s\n", str1);
    double naive_duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Naive approach time: %lf seconds\n", naive_duration);

    start = clock();
    simd_to_upper(str2);
    end = clock();
    printf("SIMD approach | Result is:%s\n", str2);
    double simd_duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("SIMD approach time: %lf seconds\n", simd_duration);

    return 0;
}

