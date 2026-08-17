#include "csr_common.h"
#include <fstream>
#include <stdexcept>
#include <vector>

AdjList read_adjacency_list(const std::string& filename)
{
  std::ifstream fin(filename);
    if (!fin.is_open())
      throw std::runtime_error("Cannot open file: " + filename);

    AdjList g;
  if (!(fin >> g.V >> g.E))
      throw std::runtime_error("Bad file header -- expected: V E");
    if (g.V <= 0)
      throw std::runtime_error("V must be > 0");

  g.adj.assign(g.V, {});   

    for (int line = 0; line < g.V; ++line)
    {
        int u, deg;
      if (!(fin >> u >> deg))
          throw std::runtime_error("Unexpected end of file at line " +
                                     std::to_string(line));
        if (u < 0 || u >= g.V)
          throw std::runtime_error("Vertex id out of range: " + std::to_string(u));
        if (deg < 0)
          throw std::runtime_error("Negative degree at vertex " + std::to_string(u));

        for (int j = 0; j < deg; ++j)
        {
          int nb;  long long w;
            if (!(fin >> nb >> w))
              throw std::runtime_error(
                "Missing neighbour/weight for vertex " + std::to_string(u));
            if (nb < 0 || nb >= g.V)
              throw std::runtime_error(
                "Neighbour out of range at vertex " + std::to_string(u));
          if (nb == u)
                throw std::runtime_error(
                  "Self-loop not allowed at vertex " + std::to_string(u));

          g.adj[u].push_back({nb, w});
        }
    }
    if (g.V > 1) {
        for (int u = 0; u < g.V; ++u)
          if (g.adj[u].empty())
              throw std::runtime_error(
                "Isolated vertex " + std::to_string(u) + " not allowed");
    }

  return g;
}
CSRGraph convert_to_csr(const AdjList& g)
{
    CSRGraph csr;
  csr.V = g.V;
    csr.E = g.E;

    csr.row_ptr.assign(g.V + 1, 0);
  for (int u = 0; u < g.V; ++u)
        csr.row_ptr[u+1] = csr.row_ptr[u] + (int)g.adj[u].size();

    int total = csr.row_ptr[g.V];   
  csr.col_idx.assign(total, 0);
    csr.values .assign(total, 0LL);

    for (int u = 0; u < g.V; ++u) {
      int pos = csr.row_ptr[u];
        for (int k = 0; k < (int)g.adj[u].size(); ++k) {
         csr.col_idx[pos] = g.adj[u][k].first;
         csr.values [pos] = g.adj[u][k].second;
         ++pos;
}
    }

  return csr;
}
bool is_connected(const CSRGraph& csr)
{
    if (csr.V == 0) return true;

  std::vector<bool> visited(csr.V, false);
    std::vector<int>  stk;
  stk.push_back(0);
    visited[0] = true;
  int seen = 1;

    while (!stk.empty()) {
      int u = stk.back(); stk.pop_back();
        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u+1]; ++i) {
          int v = csr.col_idx[i];
            if (!visited[v]) {
              visited[v] = true;
                ++seen;
              stk.push_back(v);
            }
        }
    }

  return seen == csr.V;
}