# Assignment 01 - GEMM and CSR Graph Conversion

Name: Anwesha Roy Oishi  
Entry No: 2026CSM1042  
Task: Individual

## Language and Environment

- Language: C++
- Compiler: g++ (MinGW / MSYS2 build)
- OS: Windows 11
- Compile flags: `-Wall -O2 -std=c++17`
- Timing method: `std::chrono::steady_clock`, results in milliseconds.

## Implementation

- GEMM Simple - direct triple-nested loop
- GEMM Blocking - same result, 32x32 tiling for cache reuse
- CSR conversion - adjacency list to `row_ptr` / `col_idx` arrays

Simple and Blocking give identical result matrices on every test file.

## Files

```
include/gemm.h, graph.h, csr.h
src/gemm/gemm_simple.cpp, gemm_block.cpp
src/graph/graph.cpp              (reads adjacency list file)
src/helper/csr_helper.cpp        (adjacency list -> CSR)
src/driver/main.cpp              (driver: ./assignment_01 <gemm|csr> <file>)
tests/gemm/gemm_test_0{1,2,3}.txt
tests/graph/graph_test_{01,10,100,10000,50000,100000}.txt
```

## Build and Run

```
g++ -Wall -O2 -std=c++17 -Iinclude -o assignment_01.exe src/driver/main.cpp src/gemm/gemm_simple.cpp src/gemm/gemm_block.cpp src/graph/graph.cpp src/helper/csr_helper.cpp

./assignment_01.exe gemm tests/gemm/gemm_test_01.txt
./assignment_01.exe csr tests/graph/graph_test_10000.txt
```

Or use `make`.

Can also run through the common wrapper instead of building this driver directly:
```powershell
cd ../common_wrapper
g++ -Wall -O2 -std=c++17 -o wrapper.exe wrapper.cpp
.\wrapper.exe
```
Must be run from inside `common_wrapper/`. The menu lets you compile this
driver, run GEMM or CSR on one test file or all of them or run every
test in one go.

## Input format

GEMM:
```
M K N
<A, M rows>
<B, K rows>
```

Graph (undirected adjacency list):
```
V E
u degree n1 n2 ...
```
A vertex with no neighbours: `u 0`.

## Timing

Timer runs only around the algorithm call - file I/O and printing are
excluded. Fast cases finish faster than the clock can measure in one
shot, so the driver repeats the call and averages, reporting the run
count alongside the time.

## GEMM Results

| Test | Size (M K N) | Simple Time (ms) | Blocking Time (ms) | Block Size | Status |
|---|---|---|---|---|---|
| gemm_test_01.txt | 2 3 2 | 0.0000108655 | 0.0000222658 | 32 | Pass |
| gemm_test_02.txt | 3 5 4 |  0.0000549230 | 0.0000417680 | 32 | Pass |
| gemm_test_03.txt | 6 4 6 | 0.0000603400 | 0.0000819760 | 32 | Pass |

## CSR Conversion Results

| Test | V | E | Conversion Time (ms) | Status |
|---|---|---|---|---|
| graph_test_01.txt | 5 | 5 | 0.000107 (1M runs) | Pass |
| graph_test_10.txt | 10 | 16 | 0.000144 (1M runs) | Pass |
| graph_test_100.txt | 100 | 252 | 0.000525 (100K runs) | Pass |
| graph_test_10000.txt | 10,000 | 30,297 | 0.094660 (1000 runs) | Pass |
| graph_test_50000.txt | 50,000 | 150,177 | 0.795720 (100 runs) | Pass |
| graph_test_100000.txt | 100,000 | 300,156 | 1.399140 (100 runs) | Pass |


## Complexity

| Algorithm | Time | Space |
|---|---|---|
| GEMM (both) | O(M x K x N) | O(MK + KN + MN) |
| CSR conversion | O(V + E) | O(V + E) |
