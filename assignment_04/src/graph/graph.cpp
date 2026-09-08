#include "graph.h"
#include <fstream>
#include <stdexcept>

AdjList read_undirected_adjlist(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open())
        throw std::runtime_error("Cannot open input file: " + path);

    AdjList g;
    if (!(in >> g.V >> g.E))
        throw std::runtime_error("Invalid file: missing V E header");
    if (g.V <= 0)
        throw std::runtime_error("Invalid file: V must be positive");

    g.adj.assign(g.V, {});

    for (int i = 0; i < g.V; i++) {
        int u, degree;
        if (!(in >> u >> degree))
            throw std::runtime_error("Invalid file: malformed vertex record");
        if (u < 0 || u >= g.V)
            throw std::runtime_error("Invalid file: out-of-range vertex id " + std::to_string(u));

        std::vector<int> neighbors;
        for (int k = 0; k < degree; k++) {
            int nbr;
            if (!(in >> nbr))
                throw std::runtime_error("Invalid file: degree/neighbor mismatch at vertex " + std::to_string(u));
            if (nbr < 0 || nbr >= g.V)
                throw std::runtime_error("Invalid file: out-of-range neighbor id " + std::to_string(nbr));
            if (nbr == u)
                throw std::runtime_error("Invalid file: self-loop at vertex " + std::to_string(u));
            neighbors.push_back(nbr);
        }
        g.adj[u] = neighbors;
    }
    return g;
}

AdjList read_directed_adjlist(const std::string& path, PageRankParams& params) {
    std::ifstream in(path);
    if (!in.is_open())
        throw std::runtime_error("Cannot open input file: " + path);

    AdjList g;
    if (!(in >> g.V >> g.E))
        throw std::runtime_error("Invalid file: missing V E header");
    if (g.V <= 0)
        throw std::runtime_error("Invalid file: V must be positive");

    g.adj.assign(g.V, {});

    for (int i = 0; i < g.V; i++) {
        int u, outdegree;
        if (!(in >> u >> outdegree))
            throw std::runtime_error("Invalid file: malformed vertex record");
        if (u < 0 || u >= g.V)
            throw std::runtime_error("Invalid file: out-of-range vertex id " + std::to_string(u));

        std::vector<int> neighbors;
        for (int k = 0; k < outdegree; k++) {
            int nbr;
            if (!(in >> nbr))
                throw std::runtime_error("Invalid file: outdegree/neighbor mismatch at vertex " + std::to_string(u));
            if (nbr < 0 || nbr >= g.V)
                throw std::runtime_error("Invalid file: out-of-range neighbor id " + std::to_string(nbr));
            if (nbr == u)
                throw std::runtime_error("Invalid file: self-loop at vertex " + std::to_string(u));
            neighbors.push_back(nbr);
        }
        g.adj[u] = neighbors;
    }

    std::string key;
    bool got_d = false, got_t = false, got_i = false;
    while (in >> key) {
        if (key == "DAMPING") { in >> params.damping; got_d = true; }
        else if (key == "TOLERANCE") { in >> params.tolerance; got_t = true; }
        else if (key == "MAX_ITERATIONS") { in >> params.max_iterations; got_i = true; }
        else throw std::runtime_error("Invalid file: unknown key '" + key + "'");
    }
    if (!got_d || !got_t || !got_i)
        throw std::runtime_error("Invalid file: missing DAMPING/TOLERANCE/MAX_ITERATIONS");

    if (!(params.damping > 0.0) || !(params.damping < 1.0))
        throw std::runtime_error("Invalid PageRank input: damping must be in (0,1)");
    if (!(params.tolerance > 0.0))
        throw std::runtime_error("Invalid PageRank input: tolerance must be positive");
    if (params.max_iterations <= 0)
        throw std::runtime_error("Invalid PageRank input: MAX_ITERATIONS must be positive");

    return g;
}