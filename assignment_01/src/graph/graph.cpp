#include "graph.h"
#include <fstream>
#include <iostream>

AdjList read_adjacency_list(const std::string &filename, bool &ok)
{
    AdjList graph;
    ok = false;

    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "Error: could not open file " << filename << "\n";
        return graph;
    }

    if (!(fin >> graph.V >> graph.E))
    {
        std::cout << "Error: invalid header in input file\n";
        return graph;
    }

    graph.adj.resize(graph.V);

    for (int i = 0; i < graph.V; i++)
    {
        int u, degree;
        if (!(fin >> u >> degree))
        {
            std::cout << "Error: invalid adjacency data at vertex " << i << "\n";
            return graph;
        }

        if (u < 0 || u >= graph.V)
        {
            std::cout << "Error: vertex id " << u << " out of range\n";
            return graph;
        }

        graph.adj[u].resize(degree);
        for (int j = 0; j < degree; j++)
        {
            if (!(fin >> graph.adj[u][j]))
            {
                std::cout << "Error: invalid neighbor data for vertex " << u << "\n";
                return graph;
            }
        }
    }

    ok = true;
    return graph;
}