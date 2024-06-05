#include "heuristic_solver.h"
#include <set>
#include <limits>

using namespace std;

vector<vector<int>> HeuristicSolver::solve(const vector<int>& places, const map<int, int>& demand, int capacity, Graph& graph, int& bestCost) {
    vector<vector<int>> bestCombination;
    vector<vector<int>> currentCombination;
    vector<int> route = NearestNeighbor(places, graph);
    if (VerifyCapacity(route, demand, capacity)) {
        currentCombination.push_back(route);
        int currentCost = graph.calculateRouteCost(route);
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestCombination = currentCombination;
        }
    }
    return bestCombination;
}

vector<int> HeuristicSolver::NearestNeighbor(const vector<int>& places, Graph& graph) {
    vector<int> route;
    set<int> visited;
    int current = places[0];
    route.push_back(current);
    visited.insert(current);
    while (route.size() < places.size()) {
        int nearest = -1;
        int minDistance = numeric_limits<int>::max();
        for (int place : places) {
            if (visited.find(place) == visited.end()) {
                int distance = graph.getEdgeWeight(current, place);
                if (distance < minDistance) {
                    nearest = place;
                    minDistance = distance;
                }
            }
        }
        current = nearest;
        route.push_back(current);
        visited.insert(current);
    }
    return route;
}

bool HeuristicSolver::VerifyCapacity(const vector<int>& route, const map<int, int>& demand, int capacity) {
    int total_demand = 0;
    for (auto& local : route) {
        total_demand += demand.at(local);
    }
    return total_demand <= capacity;
}
