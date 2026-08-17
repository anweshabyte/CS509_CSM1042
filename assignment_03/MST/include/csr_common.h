#pragma once
#include <string>
#include <utility>
#include <vector>

struct AdjList {
    int V = 0;
  int E = 0;
    std::vector< std::vector< std::pair<int,long long> > > adj;
};
struct CSRGraph {
  int V = 0;
    int E = 0;
  std::vector<int> row_ptr;
    std::vector<int> col_idx;
  std::vector<long long> values;
};
AdjList  read_adjacency_list(const std::string& filename);

CSRGraph convert_to_csr(const AdjList& g);

bool is_connected(const CSRGraph& csr);