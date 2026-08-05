#ifndef CSR_H
#define CSR_H
 
#include <vector>
#include "graph.h"
 
struct CSRGraph
{
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
};
 
CSRGraph convert_to_csr(const AdjList &graph);
void print_csr(const CSRGraph &csr);
 
#endif
 