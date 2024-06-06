#ifndef MPISOLVER_H
#define MPISOLVER_H

#include <vector>
#include <unordered_map>
#include <map>
#include <mpi>
#include "graph_class.h"

class MPISolver {
public:
    MPISolver(int argc, char** argv) : argc(argc), argv(argv) {}
    std::vector<std::vector<int>> solve(const std::vector<int>& places, const std::map<int, int>& demand, int capacity, int max_stops, Graph& graph, int& bestCost);
private:
    int argc;
    char** argv;
    std::vector<std::vector<int>> GenerateAllCombinations(const std::vector<int>& places, const std::map<int, int>& demand, int capacity, int max_stops, Graph& graph);
    bool coversAllCities(const std::vector<std::vector<int>>& combination, const std::vector<int>& places);
    void FindBestCombination(const std::vector<std::vector<int>>& routes, std::vector<std::vector<int>>& currentCombination, int index, const std::vector<int>& places, int& bestCost, std::vector<std::vector<int>>& bestCombination, Graph& graph, MPI_Comm comm);
    void distributeWork(const std::vector<std::vector<int>>& routes, int& start, int& end, MPI_Comm comm);
};

#endif
