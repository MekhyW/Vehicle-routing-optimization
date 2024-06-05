#ifndef HEURISTIC_SOLVER_H
#define HEURISTIC_SOLVER_H

#include <vector>
#include <map>
#include "graph_class.h"

using namespace std;

class HeuristicSolver {
public:
    static vector<vector<int>> solve(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph, int& bestCost);

private:
    static vector<vector<int>> ConstructInitialSolution(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops);
    static vector<vector<int>> LocalSearch(vector<vector<int>>& initialSolution, const map<int, int>& demand, int capacity, Graph& graph, int& bestCost, int max_stops = 6);
    static int CalculateTotalCost(const vector<vector<int>>& solution, Graph& graph);
    static vector<int> TwoOptSwap(const vector<int>& route, size_t i, size_t j);
    static bool VerifyCapacityAndStops(const vector<int>& route, const map<int, int>& demand, int capacity, int max_stops);
    static int calculateRouteCost(const vector<int>& route, Graph& graph);
    static bool verifyValidRoute(const vector<int>& route, Graph& graph);
};

#endif
