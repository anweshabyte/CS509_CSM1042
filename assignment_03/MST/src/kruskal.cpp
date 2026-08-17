#include "kruskal.h"
#include <algorithm>
#include <chrono>
#include <numeric>
struct DSU {
    std::vector<int> parent;
    std::vector<int> rank_;

    DSU(int n) {
        parent.resize(n);
        rank_.assign(n, 0);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; 

        if (rank_[a] < rank_[b]) std::swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

MSTResult kruskal_mst(const CSRGraph& csr) {
    auto startTime = std::chrono::steady_clock::now();
    std::vector<Edge> edgeList;
    edgeList.reserve(csr.E);

    for (int u = 0; u < csr.V; u++) {
        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; i++) {
            int v = csr.col_idx[i];
            if (u < v) {
                edgeList.push_back({u, v, csr.values[i]});
            }
        }
    }
    std::sort(edgeList.begin(), edgeList.end(),
              [](const Edge& a, const Edge& b) {
                  return a.w < b.w;
              });

    DSU dsu(csr.V);
    MSTResult result;

    for (const Edge& e : edgeList) {
        if (dsu.unite(e.u, e.v)) {
            result.edges.push_back(e);
            result.total_weight += e.w;
            if ((int)result.edges.size() == csr.V - 1) {
                break;
            }
        }
    }
    auto endTime = std::chrono::steady_clock::now();
    result.time_ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return result;
}