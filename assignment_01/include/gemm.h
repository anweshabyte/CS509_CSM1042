#ifndef GEMM_H
#define GEMM_H

void gemm_simple(int M, int K, int N, double *A, double *B, double *C);
void gemm_blocking(int M, int K, int N, double *A, double *B, double *C, int block_size);

#endif