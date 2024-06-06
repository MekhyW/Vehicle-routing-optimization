CXX = mpic++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3 -fopenmp -I$(INCLUDE_DIR)
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
SOLVERS_DIR = solvers

SRCS = $(SRC_DIR)/main.cpp \
       $(SOLVERS_DIR)/brute_force_solver.cpp \
	   $(SOLVERS_DIR)/brute_force_ES_solver.cpp \
       $(SOLVERS_DIR)/heuristic_solver.cpp \
       $(SOLVERS_DIR)/mpi_solver.cpp \
	   $(SOLVERS_DIR)/openmp_solver.cpp \
	   $(SOLVERS_DIR)/openmp-mpi_solver.cpp \
	   $(SRC_DIR)/graph_class.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOLVERS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: clean all
