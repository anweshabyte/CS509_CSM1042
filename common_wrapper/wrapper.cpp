#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

const string ASSIGN01_DIR = "..\\assignment_01";
const string ASSIGN01_EXE = ASSIGN01_DIR + "\\assignment_01.exe";

const vector<string> GEMM_TESTS = {
    ASSIGN01_DIR + "\\tests\\gemm\\gemm_test_01.txt",
    ASSIGN01_DIR + "\\tests\\gemm\\gemm_test_02.txt",
    ASSIGN01_DIR + "\\tests\\gemm\\gemm_test_03.txt"
};

const vector<string> GRAPH_TESTS = {
    ASSIGN01_DIR + "\\tests\\graph\\graph_test_01.txt",
    ASSIGN01_DIR + "\\tests\\graph\\graph_test_10.txt",
    ASSIGN01_DIR + "\\tests\\graph\\graph_test_100.txt",
    ASSIGN01_DIR + "\\tests\\graph\\graph_test_10000.txt",
    ASSIGN01_DIR + "\\tests\\graph\\graph_test_50000.txt",
    ASSIGN01_DIR + "\\tests\\graph\\graph_test_100000.txt"
};

bool file_exists(const string &path)
{
    ifstream f(path);
    return f.good();
}

bool compile_assignment01()
{
    cout << "Compiling assignment_01 driver...\n";
    string cmd =
        "g++ -Wall -O2 -std=c++17 -I" + ASSIGN01_DIR + "\\include -o " + ASSIGN01_EXE +
        " " + ASSIGN01_DIR + "\\src\\driver\\main.cpp" +
        " " + ASSIGN01_DIR + "\\src\\gemm\\gemm_simple.cpp" +
        " " + ASSIGN01_DIR + "\\src\\gemm\\gemm_block.cpp" +
        " " + ASSIGN01_DIR + "\\src\\graph\\graph.cpp" +
        " " + ASSIGN01_DIR + "\\src\\helper\\csr_helper.cpp";

    int result = system(cmd.c_str());
    if (result != 0)
    {
        cout << "Error: compilation failed.\n";
        return false;
    }
    cout << "Compilation successful.\n";
    return true;
}

bool ensure_built()
{
    if (file_exists(ASSIGN01_EXE))
        return true;
    return compile_assignment01();
}

vector<string> existing_files(const vector<string> &candidates)
{
    vector<string> files;
    for (const string &f : candidates)
        if (file_exists(f))
            files.push_back(f);
    return files;
}

void run_one(const string &algo, const string &testfile)
{
    if (!ensure_built())
        return;

    if (!file_exists(testfile))
    {
        cout << "Error: test file not found: " << testfile << "\n";
        return;
    }

    string cmd = ASSIGN01_EXE + " " + algo + " " + testfile;
    cout << "\n--- Running: " << cmd << " ---\n";
    cout.flush();
    int result = system(cmd.c_str());
    (void) result;
}

void run_selected(const string &algo, const vector<string> &candidates)
{
    vector<string> files = existing_files(candidates);
    if (files.empty())
    {
        cout << "Error: no test files found.\n";
        return;
    }

    cout << "\nAvailable test files:\n";
    for (size_t i = 0; i < files.size(); i++)
        cout << "  " << (i + 1) << ". " << files[i] << "\n";

    cout << "Select a test file number: ";
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > (int) files.size())
    {
        cout << "Error: invalid selection.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    run_one(algo, files[choice - 1]);
}

void run_all(const string &algo, const vector<string> &candidates)
{
    vector<string> files = existing_files(candidates);
    if (files.empty())
    {
        cout << "Error: no test files found.\n";
        return;
    }

    for (const string &f : files)
        run_one(algo, f);
}

void print_menu()
{
    cout << "\n============ CS509 Common Wrapper ============\n";
    cout << "Assignment 01 - GEMM and CSR\n";
    cout << "  1. Compile assignment_01 driver\n";
    cout << "  2. Run GEMM - select one test file\n";
    cout << "  3. Run GEMM - all test files\n";
    cout << "  4. Run CSR - select one test file\n";
    cout << "  5. Run CSR - all test files\n";
    cout << "  6. Run everything (all GEMM + all CSR tests)\n";
    cout << "  0. Exit\n";
    cout << "================================================\n";
    cout << "Choice: ";
}

int main()
{
    int choice;

    while (true)
    {
        print_menu();

        if (!(cin >> choice))
        {
            cout << "Error: invalid input.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0)
        {
            cout << "Exiting.\n";
            break;
        }
        else if (choice == 1)
        {
            compile_assignment01();
        }
        else if (choice == 2)
        {
            run_selected("gemm", GEMM_TESTS);
        }
        else if (choice == 3)
        {
            run_all("gemm", GEMM_TESTS);
        }
        else if (choice == 4)
        {
            run_selected("csr", GRAPH_TESTS);
        }
        else if (choice == 5)
        {
            run_all("csr", GRAPH_TESTS);
        }
        else if (choice == 6)
        {
            run_all("gemm", GEMM_TESTS);
            run_all("csr", GRAPH_TESTS);
        }
        else
        {
            cout << "Error: unknown option.\n";
        }
    }

    return 0;
}