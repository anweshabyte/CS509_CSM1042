#ifndef CSR_H
#define CSR_H

#include <vector>

struct CSRGraph {
    int V;                     // number of vertices
    std::vector<int> row_ptr;  // size V+1
    std::vector<int> col_idx;  // size = number of directed entries
};

#endif

