#pragma once
#include <vector>

struct Edge {
  int u;          
    int v;        
  long long w;    
};

struct MSTResult {
    std::vector<Edge> edges;    
  long long total_weight = 0; 
    double   time_ms = 0.0;  
};