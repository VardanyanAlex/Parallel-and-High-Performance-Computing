
#include <immintrin.h> // For AVX2
#include <stdio.h>
#include <time.h>

#define SIZE 10000000

void simd_add(double *a, double *b, double *result) {
    int i;
    for (i = 0; i <= SIZE - 4; i += 4) { // Process 8 floats at a time
        __m256d va = _mm256_loadu_pd(&a[i]);     // Load 8 floats from array `a`
        __m256d vb = _mm256_loadu_pd(&b[i]);     // Load 8 floats from array `b`
        __m256d vresult = _mm256_add_pd(va, vb); // Add the floats
        _mm256_storeu_pd(&result[i], vresult);  // Store the result
    }

    // Handle remaining elements (if SIZE is not a multiple of 8)
    for (; i < SIZE; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    double a[SIZE], b[SIZE], result[SIZE];

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = i * 1.0f;
        b[i] = (SIZE - i) * 1.0f;
    }

    // Measure SIMD addition
    clock_t start = clock();
    simd_add(a, b, result);
    clock_t end = clock();

    printf("SIMD Addition Time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

