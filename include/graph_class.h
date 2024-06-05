#ifndef GRAPH_CLASS_H
#define GRAPH_CLASS_H

#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

class Graph {
    unordered_map<int, vector<pair<int, int>>> adjacencies;

public:
    void addEdge(int origin, int destination, int weight);
    int calculateRouteCost(const vector<int>& route);
    bool verifyValidRoute(const vector<int>& route);
};

#endif // GRAPH_CLASS_H
