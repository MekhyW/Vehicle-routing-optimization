#include "graph_class.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void Graph::addEdge(int origin, int destination, int weight) {
    adjacencies[origin].push_back(make_pair(destination, weight));
    adjacencies[destination].push_back(make_pair(origin, weight));
}

int Graph::calculateRouteCost(const vector<int>& route) {
    vector<int> route_copy = route;
    route_copy.push_back(0);
    route_copy.insert(route_copy.begin(), 0);
    int cost = 0;
    for (size_t i = 0; i < route_copy.size() - 1; i++) {
        int origin = route_copy[i];
        int destination = route_copy[i + 1];
        for (const auto& edge : adjacencies[origin]) {
            if (edge.first == destination) {
                cost += edge.second;
                break;
            }
        }
    }
    return cost;
}

bool Graph::verifyValidRoute(const vector<int>& route) {
    for (size_t i = 0; i < route.size() - 1; i++) {
        int origin = route[i];
        int destination = route[i + 1];
        if (adjacencies.find(origin) == adjacencies.end()) {
            return false;
        }
        bool edgeFound = false;
        for (const auto& edge : adjacencies[origin]) {
            if (edge.first == destination) {
                edgeFound = true;
                break;
            }
        }
        if (!edgeFound) {
            return false;
        }
    }
    return true;
}

int Graph::getEdgeWeight(int current, int place) {
    for (const auto& edge : adjacencies[current]) {
        if (edge.first == place) {
            return edge.second;
        }
    }
    return -1;
}
