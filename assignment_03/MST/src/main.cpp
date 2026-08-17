#include "csr_common.h"
#include "kruskal.h"
#include "prim.h"
#include <iostream>
#include <string>

static void printResult(const std::string& name,
                         const MSTResult&   res,
                         int V)
{
    std::cout << "Algorithm: " << name << " MST\n";
  std::cout << "MST edges:\n";
    for (const auto& e : res.edges)
      std::cout << e.u << " " << e.v << " " << e.w << "\n";

    std::cout << "Total MST weight: " << res.total_weight << "\n";
  std::cout << "Execution time: " << res.time_ms << " ms\n";

  if (V > 1 && (int)res.edges.size() != V - 1)
        std::cout << "[WARNING] Expected " << V-1
                << " edges but got " << res.edges.size() << "\n";
  std::cout << "\n";
}

static int runMST(const std::string& filename,
                   const std::string& algo)
{
  AdjList adj;
    try {
      adj = read_adjacency_list(filename);
    } catch (const std::exception& ex) {
        std::cerr << "[ERROR] " << ex.what() << "\n";
      return 1;
    }

  CSRGraph csr = convert_to_csr(adj);
  if (!is_connected(csr)) {
        std::cerr << "[ERROR] Graph is not connected.\n"
                << "        MST requires a connected graph.\n";
      return 1;
    }

  bool didKruskal = false, didPrim = false;
    long long kw = 0, pw = 0;

  if (algo == "kruskal" || algo == "both") {
        MSTResult k = kruskal_mst(csr);
      printResult("Kruskal's", k, csr.V);
        kw = k.total_weight;
      didKruskal = true;
    }

  if (algo == "prim" || algo == "both") {
        MSTResult p = prim_mst(csr, 0);
      printResult("Prim's", p, csr.V);
        pw = p.total_weight;
      didPrim = true;
    }

  if (didKruskal && didPrim)
        std::cout << "Kruskal weight = " << kw
                << " | Prim weight = "  << pw
                  << " | Equal? " << (kw == pw ? "Yes" : "No") << "\n";

  return 0;
}
static void showMenu()
{
    std::cout << "\n==========================================\n";
  std::cout << " Assignment 3 -- MST (Kruskal / Prim)\n";
    std::cout << "==========================================\n";
  std::cout << "Input file path: ";

    std::string filename;
  std::getline(std::cin, filename);

    std::cout << "\nAlgorithm:\n";
  std::cout << "  1) Kruskal\n";
    std::cout << "  2) Prim\n";
  std::cout << "  3) Both\n";
    std::cout << "Choice: ";

  std::string choice;
    std::getline(std::cin, choice);

  std::string algo;
    if      (choice == "1") algo = "kruskal";
  else if (choice == "2") algo = "prim";
    else                    algo = "both";

  std::cout << "\n";
    runMST(filename, algo);
}

int main(int argc, char* argv[])
{
    if (argc >= 3) {
      std::string filename = argv[1];
        std::string algo     = argv[2];

      if (algo != "kruskal" && algo != "prim" && algo != "both") {
            std::cerr << "[ERROR] Use: kruskal | prim | both\n";
          return 1;
        }

      return runMST(filename, algo);
    }

  showMenu();
    return 0;
}