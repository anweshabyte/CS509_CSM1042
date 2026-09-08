#ifndef CSR_HELPER_H
#define CSR_HELPER_H

#include "graph.h"
#include "csr.h"

// Converts an adjacency-list graph into CSR format.
// This is the helper reused from Assignment 1 -- must be called BEFORE
// the timer starts, never inside the timed algorithm section.
CSRGraph convert_to_csr(const AdjList& g);

#endif