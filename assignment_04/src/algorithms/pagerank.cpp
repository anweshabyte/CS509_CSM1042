#include "pagerank.h"
#include <cmath>

PageRankResult compute_pagerank(const CSRGraph& g, double damping,
                                 double tolerance, int max_iterations) {
    int N = g.V;
    PageRankResult result;

    std::vector<int> outdeg(N);
    for (int v = 0; v < N; v++)
        outdeg[v] = g.row_ptr[v + 1] - g.row_ptr[v];

    std::vector<std::vector<int>> in_edges(N);
    for (int u = 0; u < N; u++) {
        for (int e = g.row_ptr[u]; e < g.row_ptr[u + 1]; e++)
            in_edges[g.col_idx[e]].push_back(u);
    }

    std::vector<double> rank(N, 1.0 / N);
    std::vector<double> next(N, 0.0);

    int iter = 0;
    bool converged = false;

    for (; iter < max_iterations; iter++) {
        double dangling_sum = 0.0;
        for (int u = 0; u < N; u++)
            if (outdeg[u] == 0) dangling_sum += rank[u];

        double base = (1.0 - damping) / N + damping * dangling_sum / N;

        for (int v = 0; v < N; v++) {
            double incoming = 0.0;
            for (int u : in_edges[v])
                incoming += rank[u] / outdeg[u];
            next[v] = base + damping * incoming;
        }

        double total_change = 0.0;
        for (int v = 0; v < N; v++)
            total_change += std::fabs(next[v] - rank[v]);

        rank.swap(next);

        if (total_change <= tolerance) {
            converged = true;
            iter++;
            break;
        }
    }

    result.rank = rank;
    result.iterations = iter;
    result.converged = converged;

    double sum = 0.0;
    for (double r : rank) sum += r;
    result.sum_of_ranks = sum;

    return result;
}