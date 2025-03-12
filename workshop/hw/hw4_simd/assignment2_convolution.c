
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

void naive_convolution(double* input, double* output, double* w)
{
	for (int i = 0; i < SIZE; ++i)
	{
		double input_i_minus_1 = (i - 1 < 0) ? 0.0 : input[i - 1];
		double input_i_plus_1  = (i + 1 >= SIZE) ? 0 : input[i + 1];

		output[i] = input_i_minus_1 * w[0] + input[i] * w[1] + input_i_plus_1 * w[2];
	}
}

void simd_convolution(double* input, double* output, double* w)
{
	output[0] = input[1] * w[1] + input[2] * w[2];
	
	__m256d w1 = _mm256_set1_pd(w[0]);
	__m256d w2 = _mm256_set1_pd(w[1]);
	__m256d w3 = _mm256_set1_pd(w[2]);

	int i;
	for (i = 1; i < SIZE - 8; i += 8)
	{
		__m256d i_elems = _mm256_loadu_pd(&input[i]);
		__m256d i_minus_1_elems = _mm256_loadu_pd(&input[i - 1]);
		__m256d i_plus_1_elems = _mm256_loadu_pd(&input[i + 1]);

		__m256d term1 = _mm256_mul_pd(i_minus_1_elems, w1);
		__m256d term2 = _mm256_mul_pd(i_elems, w2);
		__m256d term3 = _mm256_mul_pd(i_plus_1_elems, w3);

		__m256d sum = _mm256_add_pd(term1, term2);
		sum = _mm256_add_pd(sum, term3);

		_mm256_storeu_pd(&output[i], sum);
	}

	for (; i < SIZE - 1; i++) 
	{
        	output[i] = input[i-1] * w[0] + 
                    input[i] * w[1] + 
                    input[i+1] * w[2];
    	}
    	
	output[SIZE - 1] = input[SIZE - 2] * w[0] + input[SIZE - 1] * w[1];
}

int main()
{
	srand(time(NULL));
	double w[3] = {0.25, 0.5, 0.25};
	double input[SIZE];
	
	for (int i = 0; i < SIZE; ++i)
                input[i] = (rand() % 100) * 1.0;

	double output[SIZE];

    	clock_t start = clock();
    	naive_convolution(input, output, w);
    	clock_t end = clock();
    	printf("Naive approach | Result is:\n");
	//for (int i = 0; i < SIZE; ++i)
	//	printf("%f,", output[i]);
	printf("\n");

    	double naive_duration = (double)(end - start) / CLOCKS_PER_SEC;
    	printf("Convolution naive approach time: %lf seconds\n", naive_duration);

    	start = clock();
    	simd_convolution(input, output, w);
    	end = clock();
    	printf("SIMD approach | Result is:\n");
	//for (int i = 0; i < SIZE; ++i)
	//	printf("%f,", output[i]);
	printf("\n");

    	double simd_duration = (double)(end - start) / CLOCKS_PER_SEC;
    	printf("Convolution SIMD approach time: %lf seconds\n", simd_duration);	

	return 0;
}

