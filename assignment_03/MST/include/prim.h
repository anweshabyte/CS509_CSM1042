#pragma once
#include "csr_common.h"
#include "mst_types.h"

MSTResult prim_mst(const CSRGraph& csr, int start = 0);