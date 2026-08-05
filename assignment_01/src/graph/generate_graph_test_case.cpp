#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Usage: " << argv[0] << " <V> <avg_degree> <output_file>\n";
        return 1;
    }

    int V = atoi(argv[1]);
    int avg_degree = atoi(argv[2]);
    string outfile = argv[3];

    if (V <= 0 || avg_degree <= 0)
    {
        cout << "Error: V and avg_degree must be positive integers\n";
        return 1;
    }

    srand((unsigned int) time(NULL));

    vector<set<int>> adj(V);
    int edge_count = 0;

    for (int u = 0; u < V; u++)
    {
        int deg = 1 + (rand() % avg_degree);
        for (int k = 0; k < deg; k++)
        {
            int v = rand() % V;
            if (v == u) continue;
            if (adj[u].count(v)) continue;

            adj[u].insert(v);
            adj[v].insert(u);
            edge_count++;
        }
    }

    ofstream fout(outfile);
    if (!fout.is_open())
    {
        cout << "Error: could not create output file " << outfile << "\n";
        return 1;
    }

    fout << V << " " << edge_count << "\n";
    for (int u = 0; u < V; u++)
    {
        fout << u << " " << adj[u].size();
        for (int v : adj[u])
            fout << " " << v;
        fout << "\n";
    }

    fout.close();
    cout << "Generated graph with V=" << V << ", E=" << edge_count << " in " << outfile << "\n";
    return 0;
}