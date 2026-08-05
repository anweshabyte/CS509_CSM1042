#include "gemm.h"
#include <algorithm>

void gemm_blocking(int M, int K, int N, double *A, double *B, double *C, int block_size)
{
    for (int i = 0; i < M * N; i++)
        C[i] = 0.0;

    for (int ii = 0; ii < M; ii += block_size)
    {
        int i_end = std::min(ii + block_size, M);

        for (int jj = 0; jj < N; jj += block_size)
        {
            int j_end = std::min(jj + block_size, N);

            for (int kk = 0; kk < K; kk += block_size)
            {
                int k_end = std::min(kk + block_size, K);

                for (int i = ii; i < i_end; i++)
                {
                    for (int j = jj; j < j_end; j++)
                    {
                        double sum = C[i * N + j];
                        for (int k = kk; k < k_end; k++)
                            sum += A[i * K + k] * B[k * N + j];
                        C[i * N + j] = sum;
                    }
                }
            }
        }
    }
}