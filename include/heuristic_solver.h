#ifndef HEURISTIC_SOLVER_H
#define HEURISTIC_SOLVER_H

#include <vector>
#include <map>
#include "graph_class.h"

class HeuristicSolver {
public:
    static std::vector<std::vector<int>> solve(const vector<int>& places, const map<int, int>& demand, int capacity, Graph& graph, int& bestCost);
private:
    static std::vector<int> NearestNeighbor(const std::vector<int>& places, Graph& graph);
    static bool VerifyCapacity(const std::vector<int>& route, const std::map<int, int>& demand, int capacity);
};

#endif // HEURISTIC_SOLVER_H
