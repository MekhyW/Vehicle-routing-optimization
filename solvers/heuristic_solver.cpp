#include "heuristic_solver.h"
#include <algorithm>
#include <iostream>
#include <limits.h>

using namespace std;

vector<vector<int>> HeuristicSolver::solve(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph, int& bestCost) {
    vector<vector<int>> initialSolution = ConstructInitialSolution(places, demand, capacity, max_stops);
    vector<vector<int>> improvedSolution = LocalSearch(initialSolution, demand, capacity, graph, bestCost);
    return improvedSolution;
}

vector<vector<int>> HeuristicSolver::ConstructInitialSolution(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops) {
    vector<vector<int>> solution;
    vector<int> route;
    int remainingCapacity = capacity;
    int currentStopCount = 0;
    for (int place : places) {
        if (demand.at(place) > remainingCapacity || currentStopCount >= max_stops) {
            solution.push_back(route);
            route.clear();
            remainingCapacity = capacity;
            currentStopCount = 0;
        }
        route.push_back(place);
        remainingCapacity -= demand.at(place);
        currentStopCount++;
    }
    if (!route.empty()) {
        solution.push_back(route);
    }
    return solution;
}

vector<vector<int>> HeuristicSolver::LocalSearch(vector<vector<int>>& initialSolution, const map<int, int>& demand, int capacity, Graph& graph, int& bestCost, int max_stops) {
    vector<vector<int>> currentSolution = initialSolution;
    bestCost = CalculateTotalCost(currentSolution, graph);
    cout << "Initial cost: " << bestCost << endl;
    bool improved = true;
    while (improved) {
        improved = false;
        for (size_t routeIndex = 0; routeIndex < currentSolution.size(); ++routeIndex) {
            auto& route = currentSolution[routeIndex];
            for (size_t i = 0; i < route.size() - 1; ++i) {
                for (size_t j = i + 1; j < route.size(); ++j) {
                    vector<int> newRoute = TwoOptSwap(route, i, j);
                    if (VerifyCapacityAndStops(newRoute, demand, capacity, max_stops)) {
                        if (verifyValidRoute(newRoute, graph)) {
                            int newRouteCost = calculateRouteCost(newRoute, graph);
                            if (newRouteCost < bestCost) {
                                cout << "Improved route: " << newRouteCost << endl;
                                route = newRoute;
                                bestCost = newRouteCost;
                                improved = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return currentSolution;
}

int HeuristicSolver::CalculateTotalCost(const vector<vector<int>>& solution, Graph& graph) {
    int totalCost = 0;
    for (const auto& route : solution) {
        totalCost += calculateRouteCost(route, graph);
    }
    return totalCost;
}

vector<int> HeuristicSolver::TwoOptSwap(const vector<int>& route, size_t i, size_t j) {
    vector<int> newRoute = route;
    reverse(newRoute.begin() + i, newRoute.begin() + j + 1);
    return newRoute;
}

bool HeuristicSolver::VerifyCapacityAndStops(const vector<int>& route, const map<int, int>& demand, int capacity, int max_stops) {
    int total_demand = 0;
    unordered_map<int, int> place_count;
    for (int place : route) {
        total_demand += demand.at(place);
        place_count[place]++;
        if (total_demand > capacity || place_count[place] > max_stops) {
            return false;
        }
    }
    return true;
}

int HeuristicSolver::calculateRouteCost(const vector<int>& route, Graph& graph) {
    return graph.calculateRouteCost(route);
}

bool HeuristicSolver::verifyValidRoute(const vector<int>& route, Graph& graph) {
    return graph.verifyValidRoute(route);
}
