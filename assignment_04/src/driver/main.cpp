#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <stdexcept>

#include "graph.h"
#include "csr.h"
#include "csr_helper.h"
#include "vertex_coloring.h"
#include "pagerank.h"

void print_usage(const char* prog) {
    std::cout << "Usage:\n"
              << "  " << prog << " coloring <input_file.txt>\n"
              << "  " << prog << " pagerank <input_file.txt>\n";
}

void run_coloring(const std::string& path) {
    AdjList g = read_undirected_adjlist(path);     
    CSRGraph csr = convert_to_csr(g);               

    auto t0 = std::chrono::high_resolution_clock::now();
    ColoringResult res = greedy_vertex_coloring(csr); 
    auto t1 = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    std::cout << "Algorithm: Greedy Vertex Coloring\n";
    std::cout << "Vertex colors:\n";
    for (int v = 0; v < csr.V; v++)
        std::cout << v << " " << res.color[v] << "\n";
    std::cout << "Colors used: " << res.colors_used << "\n";
    std::cout << "Execution time: " << ms << " ms\n";
    std::cout << "Valid coloring: " << (res.valid ? "Yes" : "No") << "\n";
}

void run_pagerank(const std::string& path) {
    PageRankParams params;
    AdjList g = read_directed_adjlist(path, params); 
    CSRGraph csr = convert_to_csr(g);                  

    auto t0 = std::chrono::high_resolution_clock::now();
    PageRankResult res = compute_pagerank(csr, params.damping, params.tolerance, params.max_iterations); // timed
    auto t1 = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    std::cout << "Algorithm: PageRank\n";
    std::cout << "Damping: " << params.damping << "\n";
    std::cout << "Vertex ranks:\n";
    std::cout << std::fixed << std::setprecision(6);
    for (int v = 0; v < csr.V; v++)
        std::cout << v << " " << res.rank[v] << "\n";
    std::cout << "Sum of ranks: " << res.sum_of_ranks << "\n";
    std::cout.unsetf(std::ios::fixed);
    std::cout << "Iterations: " << res.iterations << "\n";
    std::cout << "Converged: " << (res.converged ? "true" : "false") << "\n";
    std::cout << "Execution time: " << ms << " ms\n";
}

void interactive_menu() {
    std::cout << "==== Assignment 4: Individual Task ====\n";
    std::cout << "1. Vertex Coloring\n2. PageRank\n";
    std::cout << "Choose an option (1/2): ";
    int choice;
    std::cin >> choice;

    std::cout << "Enter input file path: ";
    std::string path;
    std::cin >> path;

    try {
        if (choice == 1) run_coloring(path);
        else if (choice == 2) run_pagerank(path);
        else std::cerr << "Invalid choice.\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        interactive_menu();
        return 0;
    }
    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    std::string algo = argv[1];
    std::string path = argv[2];

    try {
        if (algo == "coloring") run_coloring(path);
        else if (algo == "pagerank") run_pagerank(path);
        else {
            std::cerr << "Unknown algorithm: " << algo << "\n";
            print_usage(argv[0]);
            return 1;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}