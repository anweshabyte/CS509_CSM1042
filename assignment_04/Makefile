CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude

SRC = src/driver/main.cpp \
      src/graph/graph.cpp \
      src/helper/csr_helper.cpp \
      src/algorithms/vertex_coloring.cpp \
      src/algorithms/pagerank.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = assignment4

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean