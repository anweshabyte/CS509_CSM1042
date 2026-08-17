# Assignment 03 - Minimum Spanning Tree (MST)

Name: Anwesha Roy Oishi

Entry No: 2026CSM1042

Task: Individual

---

## Language and Environment

- Language: C++
- Compiler: g++ 
- OS: Windows 11
- Compile flags: `-O2 -std=c++17`
- Timing method: `std::chrono::steady_clock`, results in milliseconds

---

## Algorithms Implemented

- **Kruskal's Algorithm** — sorts all edges by weight, uses DSU (Disjoint Set Union) with path compression and union by rank to greedily pick edges without forming cycles
- **Prim's Algorithm** — grows the MST one vertex at a time using a min-heap (priority queue), always picking the cheapest edge that connects a new vertex

---

## Files

```
MST/
├── include/
│   ├── mst_types.h        
│   ├── csr_common.h       
│   ├── kruskal.h          (kruskal_mst() declaration)
│   └── prim.h             (prim_mst() declaration)
├── src/
│   ├── csr_common.cpp     
│   ├── kruskal.cpp        (Kruskal's algorithm with DSU)
│   ├── prim.cpp           (Prim's algorithm with min-heap)
│   └── main.cpp           (driver: CLI + interactive menu)
├── test_files/
├── build/
└── output/
```

---

## Build and Run

```
g++ -O2 -std=c++17 -Iinclude src/csr_common.cpp src/kruskal.cpp src/prim.cpp src/main.cpp -o build/mst_program
```

Run with command line arguments:
```
./build/mst_program test_files/mst_10.txt both
./build/mst_program test_files/mst_10.txt kruskal
./build/mst_program test_files/mst_10.txt prim
```

Run in interactive menu mode (no arguments):
```
./build/mst_program
```

---

## Input Format

Weighted undirected adjacency list:

```
V E
u0 degree  neighbour1 weight1  neighbour2 weight2  ...
u1 degree  neighbour1 weight1  ...
...
```

- V = number of vertices (0 to V-1)
- E = number of undirected edges (each edge counted once)
---

## MST Results Table

| File             | Vertices      | Edges      | Kruskal Wt. | Prim Wt. | Kruskal Time | Prim Time | Equal? | Status |
|------------------|---------|---------|-------------|----------|--------------|-----------|--------|--------|
| mst_10.txt       | 10      | 20      | 158         | 158      | 0 ms         | 0 ms      | Yes    | Pass   |
| mst_100.txt      | 100     | 250     | 2402        | 2402     | 0 ms         | 0 ms      | Yes    | Pass   |
| mst_10000.txt    | 10,000  | 25,000  | 238871      | 238871   | 0 ms         | 6.015 ms  | Yes    | Pass   |
| mst_50000.txt    | 50,000  | 120,000 | 1238906     | 1238906  | 15.977 ms    | 32.743 ms | Yes    | Pass   |
| mst_100000.txt   | 100,000 | 250,000 | 2379770     | 2379770  | 22.819 ms    | 64.58 ms  | Yes    | Pass   |

