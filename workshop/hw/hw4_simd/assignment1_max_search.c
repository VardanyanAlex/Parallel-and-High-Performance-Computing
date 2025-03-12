
#include <immintrin.h> // For AVX2
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define SIZE 1000000

int naive_max_search(int* arr)
{
    int max = -1;

    for (int i = 0; i < SIZE; i++) {
        if (arr[i] > max)
	    max = arr[i];
    }

    return max;
}

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


int main() {
    srand(time(NULL));	
    int arr[SIZE];

    // Initialize the array
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100 + 1;
    }

    clock_t start = clock();
    int max = naive_max_search(arr);
    clock_t end = clock();
    printf("Naive approach | Max value is:%d\n", max);
    double naive_duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Max search naive approach time: %lf seconds\n", naive_duration);

    start = clock();
    max = simd_max_search(arr);
    end = clock();
    printf("SIMD approach | Max value is:%d\n", max);
    double simd_duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Max search SIMD approach time: %lf seconds\n", simd_duration);

    return 0;
}

