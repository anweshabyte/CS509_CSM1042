#include "vertex_coloring.h"
#include <algorithm>
#include <numeric>

ColoringResult greedy_vertex_coloring(const CSRGraph& g) {
    ColoringResult result;
    int V = g.V;
    result.color.assign(V, -1);

    std::vector<int> degree(V);
    for (int v = 0; v < V; v++)
        degree[v] = g.row_ptr[v + 1] - g.row_ptr[v];

    std::vector<int> order(V);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        if (degree[a] != degree[b]) return degree[a] > degree[b];
        return a < b;
    });

    int max_color_seen = -1;
    std::vector<bool> used;

    for (int v : order) {
        used.assign(max_color_seen + 2, false);
        for (int e = g.row_ptr[v]; e < g.row_ptr[v + 1]; e++) {
            int nbr = g.col_idx[e];
            int c = result.color[nbr];
            if (c != -1 && c < (int)used.size())
                used[c] = true;
        }
        int chosen = 0;
        while (chosen < (int)used.size() && used[chosen]) chosen++;
        result.color[v] = chosen;
        if (chosen > max_color_seen) max_color_seen = chosen;
    }

    result.colors_used = max_color_seen + 1;
    result.valid = validate_coloring(g, result.color);
    return result;
}

bool validate_coloring(const CSRGraph& g, const std::vector<int>& color) {
    for (int v = 0; v < g.V; v++) {
        for (int e = g.row_ptr[v]; e < g.row_ptr[v + 1]; e++) {
            int nbr = g.col_idx[e];
            if (color[v] == color[nbr]) return false;
        }
    }
    return true;
}