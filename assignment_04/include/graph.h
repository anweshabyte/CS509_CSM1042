#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

struct AdjList {
    int V = 0;
    int E = 0;
    std::vector<std::vector<int>> adj;
};
struct PageRankParams {
    double damping = 0.85;
    double tolerance = 0.0001;
    int max_iterations = 100;
};

AdjList read_undirected_adjlist(const std::string& path);

AdjList read_directed_adjlist(const std::string& path, PageRankParams& params);

#endif
