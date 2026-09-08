#include "csr_helper.h"

CSRGraph convert_to_csr(const AdjList& g) {
    CSRGraph csr;
    csr.V = g.V;
    csr.row_ptr.assign(g.V + 1, 0);

    // row_ptr[v+1] = degree of vertex v (temporarily)
    for (int v = 0; v < g.V; v++) {
        csr.row_ptr[v + 1] = (int)g.adj[v].size();
    }

    // prefix sum -> standard CSR offsets
    for (int v = 0; v < g.V; v++) {
        csr.row_ptr[v + 1] += csr.row_ptr[v];
    }

    csr.col_idx.resize(csr.row_ptr[g.V]);
    std::vector<int> cursor = csr.row_ptr;
    for (int v = 0; v < g.V; v++) {
        for (int nbr : g.adj[v]) {
            csr.col_idx[cursor[v]] = nbr;
            cursor[v]++;
        }
    }
    return csr;
}