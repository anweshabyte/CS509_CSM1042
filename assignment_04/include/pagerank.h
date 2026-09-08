#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>
#include "csr.h"

struct PageRankResult {
    std::vector<double> rank;
    int iterations = 0;
    bool converged = false;
    double sum_of_ranks = 0.0;
};

// PR(v) = (1-d)/N + d * sum over u->v of ( PR(u) / outdegree(u) )
PageRankResult compute_pagerank(const CSRGraph& g, double damping,
                                 double tolerance, int max_iterations);

#endif