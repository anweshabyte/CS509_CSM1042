#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <functional>
#include "gemm.h"
#include "graph.h"
#include "csr.h"

using namespace std;
using namespace std::chrono;

static double time_it(const std::function<void()> &func, long long &out_repeats)
{
    const double MIN_TOTAL_MS = 50.0;
    const long long MAX_REPEATS = 20000000LL;

    func();

    long long repeats = 1;
    double elapsed_ms = 0.0;

    while (true)
    {
        auto start = steady_clock::now();
        for (long long i = 0; i < repeats; i++)
            func();
        auto end = steady_clock::now();

        elapsed_ms = duration<double, std::milli>(end - start).count();

        if (elapsed_ms >= MIN_TOTAL_MS || repeats >= MAX_REPEATS)
            break;

        repeats *= 10;
    }

    out_repeats = repeats;
    return elapsed_ms / (double) repeats;
}

static double *read_matrix(ifstream &fin, int rows, int cols, bool &ok)
{
    double *mat = new double[rows * cols];
    for (int i = 0; i < rows * cols; i++)
    {
        if (!(fin >> mat[i]))
        {
            cout << "Error: bad matrix data in input file\n";
            ok = false;
            return mat;
        }
    }
    ok = true;
    return mat;
}

static void print_matrix(double *mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << mat[i * cols + j] << " ";
        cout << "\n";
    }
}

static int run_gemm(const string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Error: could not open file " << filename << "\n";
        return 1;
    }

    int M, K, N;
    if (!(fin >> M >> K >> N))
    {
        cout << "Error: invalid header in input file\n";
        return 1;
    }

    bool ok;
    double *A = read_matrix(fin, M, K, ok);
    if (!ok) return 1;
    double *B = read_matrix(fin, K, N, ok);
    if (!ok) return 1;
    double *C1 = new double[M * N];
    double *C2 = new double[M * N];
    fin.close();

    int block_size = 32;

    long long repeats1;
    double time_simple = time_it([&]() { gemm_simple(M, K, N, A, B, C1); }, repeats1);

    cout << "Algorithm: GEMM Simple\n";
    cout << "Result matrix:\n";
    print_matrix(C1, M, N);
    cout << "Execution time: " << time_simple << " ms (avg over " << repeats1 << " runs)\n\n";

    long long repeats2;
    double time_block = time_it([&]() { gemm_blocking(M, K, N, A, B, C2, block_size); }, repeats2);

    cout << "Algorithm: GEMM Blocking\n";
    cout << "Result matrix:\n";
    print_matrix(C2, M, N);
    cout << "Execution time: " << time_block << " ms (avg over " << repeats2 << " runs)\n";

    delete[] A;
    delete[] B;
    delete[] C1;
    delete[] C2;
    return 0;
}

static int run_csr(const string &filename)
{
    bool ok;
    AdjList graph = read_adjacency_list(filename, ok);
    if (!ok) return 1;

    CSRGraph csr;
    long long repeats;
    double conv_time = time_it([&]() { csr = convert_to_csr(graph); }, repeats);

    cout << "Algorithm: CSR Conversion\n";
    cout << "Vertices: " << graph.V << ", Edges (declared): " << graph.E << "\n";
    print_csr(csr);
    cout << "Conversion time: " << conv_time << " ms (avg over " << repeats << " runs)\n";

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " <gemm|csr> <input_file>\n";
        return 1;
    }

    string algo = argv[1];
    string filename = argv[2];

    if (algo == "gemm")
        return run_gemm(filename);
    else if (algo == "csr")
        return run_csr(filename);

    cout << "Error: unknown algorithm '" << algo << "'. Use 'gemm' or 'csr'.\n";
    return 1;
}