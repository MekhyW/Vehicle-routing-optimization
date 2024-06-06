#ifndef OPENMP_SOLVER_H
#define OPENMP_SOLVER_H

#include "graph_class.h"
#include <vector>
#include <map>

using namespace std;

class OpenMPSolver {
public:
    static vector<vector<int>> solve(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph, int& bestCost);

private:
    static bool VerifyCapacityAndStops(const vector<int>& route, const map<int, int>& demand, int capacity, int max_stops);
    static vector<vector<int>> GenerateAllCombinations(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph);
    static bool coversAllCities(const vector<vector<int>>& combination, const vector<int>& places);
    static void FindBestCombination(const vector<vector<int>>& routes, vector<vector<int>>& currentCombination, size_t index, const vector<int>& places, int& bestCost, vector<vector<int>>& bestCombination, Graph& graph);
};

#endif
