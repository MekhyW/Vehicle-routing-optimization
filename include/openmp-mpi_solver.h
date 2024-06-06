#ifndef OPENMP_MPI_SOLVER_H
#define OPENMP_MPI_SOLVER_H

#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <set>
#include <mpi.h>
#include "graph_class.h"

using namespace std;

class OpenMPMPISolver {
public:
    vector<vector<int>> GenerateAllCombinations(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph);
    bool coversAllCities(const vector<vector<int>>& combination, const vector<int>& places);
    void distributeWork(const vector<vector<int>>& routes, int& start, int& end, MPI_Comm comm);
    void FindBestCombination(const vector<vector<int>>& routes, vector<vector<int>>& currentCombination, int index, const vector<int>& places, int& bestCost, vector<vector<int>>& bestCombination, Graph& graph, MPI_Comm comm);
};

#endif
