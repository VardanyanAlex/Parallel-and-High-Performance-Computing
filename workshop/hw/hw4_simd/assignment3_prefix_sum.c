
#include <immintrin.h> // For AVX2
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define SIZE 20

void naive_prefix_sum(int* arr)
{
    for (int i = 1; i < SIZE; i++) {
        arr[i] = arr[i - 1] + arr[i];
    }
}

void simd_prefix_sum(int* arr)
{
    int i = 1;
    for (; i < 8 && i < SIZE; ++i)
	arr[i] = arr[i - 1] + arr[i];

    __m256i prev_sum = _mm256_set1_epi32(arr[7]); 
    for (; i < SIZE - 8; i += 8)
    {
        __m256i data = _mm256_loadu_si256((__m256i*)&arr[i]);  
        data = _mm256_add_epi32(data, prev_sum);
        _mm256_storeu_si256((__m256i*)&arr[i], data);

        // set prev_sum elements to last element of this block
        int temp[8];
        _mm256_storeu_si256((__m256i*)temp, data);
        prev_sum = _mm256_set1_epi32(temp[7]);
    }

    for (; i < SIZE; ++i)
    {
    	arr[i] = arr[i - 1] + arr[i];
    }
}

int main() 
{
    srand(time(NULL));
    int arr1[SIZE], arr2[SIZE];

    // Initialize the array
    for (int i = 0; i < SIZE; i++) 
    {
        int a = rand() % 11;
	arr1[i] = a;
	arr2[i] = a;
	printf("%d, ", arr1[i]);
    }
    printf("\n");

    // naive
    clock_t start = clock();
    naive_prefix_sum(arr1);
    clock_t end = clock();
    for (int i = 0; i < SIZE; ++i)
	printf("%d, ", arr1[i]);
    
    double naive_duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Naive approach time: %lf seconds\n", naive_duration);

    // simd
    start = clock();
    simd_prefix_sum(arr2);
    end = clock();
    for (int i = 0; i < SIZE; ++i)
	printf("%d, ", arr2[i]);

    double simd_duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("SIMD approach time: %lf seconds\n", simd_duration);

    return 0;
}

