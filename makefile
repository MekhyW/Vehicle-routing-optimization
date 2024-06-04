CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

SRC_DIR = .
BUILD_DIR = ./build
SOLVERS_DIR = ./solvers
INCLUDE_DIR = ./include

SRCS = $(SRC_DIR)/main.cpp \
       $(SOLVERS_DIR)/brute_force_solver.cpp \
       $(SOLVERS_DIR)/heuristic_solver.cpp \
       $(SOLVERS_DIR)/mpi_solver.cpp \
	   $(SOLVERS_DIR)/openmp_solver.cpp \
	   $(SOLVERS_DIR)/openmp-mpi_solver.cpp

OBJS = $(BUILD_DIR)/main.o \
	   $(BUILD_DIR)/brute_force_solver.o \
	   $(BUILD_DIR)/heuristic_solver.o \
	   $(BUILD_DIR)/mpi_solver.o \
	   $(BUILD_DIR)/openmp_solver.o \
	   $(BUILD_DIR)/openmp-mpi_solver.o

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/%.o: $(SOLVERS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
