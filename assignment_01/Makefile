CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17 -Iinclude

TARGET = assignment_01
GENTOOL = gen_graph

DRIVER_SRC = src/driver/main.cpp
GEMM_SRC = src/gemm/gemm_simple.cpp src/gemm/gemm_block.cpp
GRAPH_SRC = src/graph/graph.cpp
HELPER_SRC = src/helper/csr_helper.cpp

all: $(TARGET)

$(TARGET): $(DRIVER_SRC) $(GEMM_SRC) $(GRAPH_SRC) $(HELPER_SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DRIVER_SRC) $(GEMM_SRC) $(GRAPH_SRC) $(HELPER_SRC)

gen_graph: src/graph/generate_graph_test_case.cpp
	$(CXX) $(CXXFLAGS) -o $(GENTOOL) src/graph/generate_graph_test_case.cpp

run_gemm: $(TARGET)
	./$(TARGET) gemm tests/gemm/gemm_test_01.txt

run_csr: $(TARGET)
	./$(TARGET) csr tests/graph/graph_test_01.txt

clean:
	rm -f $(TARGET) $(GENTOOL)