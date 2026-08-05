#include "csr.h"
#include <iostream>

CSRGraph convert_to_csr(const AdjList &graph)
{
    CSRGraph csr;
    csr.row_ptr.resize(graph.V + 1, 0);

    for (int i = 0; i < graph.V; i++)
        csr.row_ptr[i + 1] = csr.row_ptr[i] + (int) graph.adj[i].size();

    csr.col_idx.resize(csr.row_ptr[graph.V]);

    for (int i = 0; i < graph.V; i++)
    {
        int pos = csr.row_ptr[i];
        for (size_t j = 0; j < graph.adj[i].size(); j++)
            csr.col_idx[pos + j] = graph.adj[i][j];
    }

    return csr;
}

void print_csr(const CSRGraph &csr)
{
    std::cout << "row_ptr (" << csr.row_ptr.size() << " values):\n";
    for (size_t i = 0; i < csr.row_ptr.size(); i++)
        std::cout << csr.row_ptr[i] << " ";
    std::cout << "\n";

    std::cout << "col_idx (" << csr.col_idx.size() << " values):\n";
    for (size_t i = 0; i < csr.col_idx.size(); i++)
        std::cout << csr.col_idx[i] << " ";
    std::cout << "\n";
}