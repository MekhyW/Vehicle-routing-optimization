#include "brute_force_solver.h"
#include <set>
#include <stack>
#include <unordered_map>

using namespace std;

vector<vector<int>> BruteForceSolver::solve(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph, int& bestCost) {
    vector<vector<int>> routes = GenerateAllCombinations(places, demand, capacity, max_stops, graph);
    vector<vector<int>> currentCombination;
    vector<vector<int>> bestCombination;
    FindBestCombination(routes, currentCombination, 0, places, bestCost, bestCombination, graph);
    return bestCombination;
}

bool BruteForceSolver::VerifyCapacityAndStops(const vector<int>& route, const map<int, int>& demand, int capacity, int max_stops) {
    int total_demand = 0;
    unordered_map<int, int> place_count;
    for (auto& local : route) {
        total_demand += demand.at(local);
        place_count[local]++;
        if (place_count[local] > max_stops) { return false; }
    }
    return total_demand <= capacity;
}

vector<vector<int>> BruteForceSolver::GenerateAllCombinations(const vector<int>& places, const map<int, int>& demand, int capacity, int max_stops, Graph& graph) {
    vector<vector<int>> routes;
    int n = places.size();
    for (int i = 1; i < (1 << n); i++) {
        vector<int> route;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                route.push_back(places[j]);
            }
        }
        if (VerifyCapacityAndStops(route, demand, capacity, max_stops)) {
            if (graph.verifyValidRoute(route)) {
                routes.push_back(route);
            }
        }
    }
    return routes;
}

bool BruteForceSolver::coversAllCities(const vector<vector<int>>& combination, const vector<int>& places) {
    set<int> coveredCities;
    for (const auto& route : combination) {
        for (int city : route) {
            coveredCities.insert(city);
        }
    }
    return coveredCities.size() == places.size();
}

void BruteForceSolver::FindBestCombination(const vector<vector<int>>& routes, vector<vector<int>>& currentCombination, int index, const vector<int>& places, int& bestCost, vector<vector<int>>& bestCombination, Graph& graph) {
    stack<pair<int, int>> stack;
    stack.push(make_pair(index, 0));
    while (!stack.empty()) {
        pair<int, int> top = stack.top();
        stack.pop();
        int i = top.first;
        int option = top.second;
        if (option == 0) {
            if (coversAllCities(currentCombination, places)) {
                int totalCost = 0;
                for (const auto& route : currentCombination) {
                    totalCost += graph.calculateRouteCost(route);
                }
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestCombination = currentCombination;
                }
                continue;
            }
        }
        if (option == 0 && static_cast<size_t>(i) < routes.size()) {
            currentCombination.push_back(routes[i]);
            stack.push(make_pair(i, 1));
            stack.push(make_pair(i + 1, 0));
        } else if (option == 1) {
            currentCombination.pop_back();
            stack.push(make_pair(i + 1, 0));
        }
    }
}
