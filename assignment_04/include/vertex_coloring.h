#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include <vector>
#include "csr.h"

struct ColoringResult {
    std::vector<int> color;
    int colors_used = 0;
    bool valid = true;
};

ColoringResult greedy_vertex_coloring(const CSRGraph& g);

bool validate_coloring(const CSRGraph& g, const std::vector<int>& color);

#endif