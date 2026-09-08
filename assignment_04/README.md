# Assignment 04 - Vertex Coloring & PageRank

Name: Anwesha Roy Oishi

Entry No: 2026CSM1042

Task: Individual

## Language and Environment

- Language: C++
- Compiler: g++
- OS: Windows 11
- Compile flags: `-O2 -std=c++17`
- Timing method: `std::chrono::high_resolution_clock`, results in milliseconds

## Algorithms Implemented

- **Vertex Coloring (Greedy, Welsh-Powell)** — computes vertex degrees from the CSR representation, orders vertices by non-increasing degree, then greedily assigns each vertex the smallest color index not used by any already-colored neighbour
- **PageRank** — iteratively computes rank of each vertex in a directed graph using `PR(v) = (1-d)/N + d * sum(PR(u)/outdegree(u))`, redistributing dangling-vertex rank evenly across all vertices, until the total change falls below tolerance or max iterations is reached

## Files
```
assignment_04/
├── include/
│ ├── graph.h                   (AdjList struct + file reader declarations)
│ ├── csr.h                     (CSRGraph struct)
│ ├── csr_helper.h              (convert_to_csr() declaration)
│ ├── vertex_coloring.h         (greedy_vertex_coloring() declaration)
│ └── pagerank.h                (compute_pagerank() declaration)
├── src/
│ ├── driver/main.cpp           (driver: CLI + interactive menu)
│ ├── graph/graph.cpp           (input reading + validation)
│ ├── helper/csr_helper.cpp     (adjacency-list -> CSR conversion)
│ └── algorithms/
│ ├── vertex_coloring.cpp       (Greedy Welsh-Powell coloring)
│ └── pagerank.cpp              (PageRank iterative computation)
├── testcases/
└── output/
```

## Build and Run :
```
g++ -O2 -std=c++17 -Iinclude src/driver/main.cpp src/graph/graph.cpp src/helper/csr_helper.cpp src/algorithms/vertex_coloring.cpp src/algorithms/pagerank.cpp -o assignment_04
```

```
Run with command line arguments:
./assignment_04 coloring testcases/color_10.txt
./assignment_04 pagerank testcases/pagerank_10.txt

Run in interactive menu mode (no arguments):
./assignment_04
```

## Input Format :
```
Vertex Coloring — unweighted, undirected adjacency list:
V E
u0 degree neighbour1 neighbour2 ...
u1 degree neighbour1 neighbour2 ...
...

PageRank — unweighted, directed adjacency list + parameters:
V E
u0 outdegree neighbour1 neighbour2 ...
u1 outdegree neighbour1 neighbour2 ...
...
DAMPING d
TOLERANCE epsilon
MAX_ITERATIONS n

- V = number of vertices (0 to V-1)
- E = number of edges (undirected: counted once; directed: counted once per outgoing edge)
```

## Vertex Coloring Results Table :

| File             | Vertices | Edges  | Colors Used  | Valid? | Time      | Status |
|------------------|----------|--------|--------------|--------|-----------|--------|
| color_10.txt     | 10       | 20     | 3            | Yes    | 0 ms      | Pass   |
| color_100.txt    | 100      | 200    | 4            | Yes    | 0 ms      | Pass   |
| color_1000.txt   | 1,000    | 2,000  | 5            | Yes    | 0 ms      | Pass   |
| color_10000.txt  | 10,000   | 20,000 | 5            | Yes    | 0.834 ms  | Pass   |

## PageRank Results Table :

| File                | Vertices | Edges   | Damping | Sum of Ranks | Iterations | Converged | Time       | Status |
|---------------------|----------|---------|---------|--------------|------------|-----------|------------|--------|
| pagerank_10.txt     | 10       | 20      | 0.85    | 1.000000     | 15         | true      | 0 ms       | Pass   |
| pagerank_100.txt    | 100      | 200     | 0.85    | 1.000000     | 15         | true      | 0 ms       | Pass   |
| pagerank_1000.txt   | 1,000    | 2,000   | 0.85    | 1.000000     | 17         | true      | 10.394 ms  | Pass   |
| pagerank_10000.txt  | 10,000   | 20,000  | 0.85    | 1.000000     | 17         | true      | 17.292 ms  | Pass   |
| pagerank_50000.txt  | 50,000   | 100,000 | 0.85    | 1.000000     | 17         | true      | 86.107 ms  | Pass   |

