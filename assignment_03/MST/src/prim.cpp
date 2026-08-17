
#include "prim.h"
#include <chrono>
#include <climits>
#include <queue>
#include <vector>

MSTResult prim_mst(const CSRGraph& csr, int start)
{
  using clk = std::chrono::steady_clock;
    auto t0 = clk::now();

  const int V = csr.V;

  std::vector<bool> inMST(V, false);
  std::vector<long long> key(V, LLONG_MAX);

  std::vector<int> parent(V, -1);
    using Item = std::pair<long long, int>;
  std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pq;

  key[start] = 0;
    pq.push({0, start});

  MSTResult res;
    res.edges.reserve(V > 0 ? V - 1 : 0);
  int taken = 0;

    while (!pq.empty() && taken < V)
    {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;  
      inMST[u] = true;
        ++taken;

      if (parent[u] != -1) {
            Edge e;
            e.u = parent[u];
            e.v = u;
            e.w = key[u];
            res.edges.push_back(e);
          res.total_weight += key[u];
        }

      for (int i = csr.row_ptr[u]; i < csr.row_ptr[u+1]; ++i)
        {
            int v  = csr.col_idx[i];
          long long w = csr.values[i];

          if (!inMST[v] && w < key[v]) {
                key[v] = w;
              parent[v] = u;
                pq.push({w, v});  
            }
        }
    }

  auto t1 = clk::now();

  res.time_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return res;
}