#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

struct AdjList
{
    int V;
    int E;
    std::vector<std::vector<int>> adj;
};

AdjList read_adjacency_list(const std::string &filename, bool &ok);

#endif