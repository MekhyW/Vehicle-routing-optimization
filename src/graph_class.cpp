#include "graph_class.h"

void Graph::addEdge(int origin, int destination, int weight) {
    adjacencies[origin].push_back(make_pair(destination, weight));
}

int Graph::calculateRouteCost(const vector<int>& route) {
    vector<int> route_copy = route;
    route_copy.push_back(0);
    route_copy.insert(route_copy.begin(), 0);
    int cost = 0;
    for (int i = 0; i < route_copy.size() - 1; i++) {
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
    for (int i = 0; i < route.size() - 1; i++) {
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
