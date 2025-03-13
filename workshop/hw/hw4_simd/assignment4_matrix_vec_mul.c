
#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 5
#define N 20

double* mul_matrix_vec(double matrix[M][N], double* vec)
{
	double* res = (double*)malloc(M * sizeof(double));
	//for (int i = 0; i < M; ++i)
	//	res[i] = (double*)malloc(N * sizeof(double));

        for (int i = 0; i < M; ++i)
        {
		res[i] = 0;
		for (int j = 0; j < N; ++j)
			res[i] += matrix[i][j] * vec[j];
        }

	return res;
}


double* simd_matrix_vec_mul(double matrix[M][N], double* vec)
{
	if (N < 8)
		return mul_matrix_vec(matrix, vec);
	
	double* res = (double*)malloc(M * sizeof(double));
	
	for (int i = 0; i < M; ++i)
        {
		res[i] = 0;
		int j = 0;
		__m256d res_sum = _mm256_setzero_pd();
		double sum[8];

		for (; j < N - 8; j += 8)
        	{
			__m256d mat_elems = _mm256_loadu_pd(&matrix[i][j]);
                	__m256d vec_elems = _mm256_loadu_pd(&vec[j]);
 			
			__m256d multiplied = _mm256_mul_pd(mat_elems, vec_elems);
			res_sum = _mm256_add_pd(multiplied, res_sum);
		}
		_mm256_storeu_pd(&sum[0], res_sum);
		for (int k = 0; k < 8; ++k)
			res[i] += sum[k];

		for(; j < N; ++j)
			res[i] += matrix[i][j] * vec[j];
	}
}


int main()
{
        srand(time(NULL));
        double matrix[M][N];
	for (int i = 0; i < M; ++i)
        	for (int j = 0; j < N; ++j)
			matrix[i][j] = (rand() % 6) * 1.0;


	double vec[N];
	for (int j = 0; j < N; ++j)
		vec[j] = (rand() % 6) * 1.0;

        clock_t start = clock();
        double* res = mul_matrix_vec(matrix, vec);
        clock_t end = clock();

	for (int i = 0; i < M; ++i)
		printf("%f, ", res[i]);	
	printf("\n");

	printf("Naive approach | Result is:\n");
        //for (int i = 0; i < SIZE; ++i)
        //      printf("%f,", output[i]);
        printf("\n");

        double naive_duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Naive approach time: %lf seconds\n", naive_duration);

        start = clock();
        simd_matrix_vec_mul(matrix, vec);
        end = clock();
        printf("SIMD approach | Result is:\n");
        
	for (int i = 0; i < M; ++i)
		printf("%f, ", res[i]);	
        printf("\n");

        double simd_duration = (double)(end - start) / CLOCKS_PER_SEC;
        printf("SIMD approach time: %lf seconds\n", simd_duration);

        return 0;
}

