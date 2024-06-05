#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include "graph_class.h"
#include "brute_force_solver.h"

using namespace std;

void ReadGraph(const string& file, map<int, int>& demand, vector<tuple<int, int, int>>& edges, vector<int>& places, Graph& graph) {
    ifstream infile(file);
    if (infile.is_open()) {
        int N;
        infile >> N;
        N -= 1;
        for (int i = 1; i <= N; i++) {
            places.push_back(i);
        }
        for (int i = 0; i < N; i++) {
            int id_no, demand_no;
            infile >> id_no >> demand_no;
            demand[id_no] = demand_no;
        }
        int K;
        infile >> K;
        for (int i = 0; i < K; i++) {
            int id_no1, id_no2, cost;
            infile >> id_no1 >> id_no2 >> cost;
            edges.push_back(make_tuple(id_no1, id_no2, cost));
            graph.addEdge(id_no1, id_no2, cost);
        }
    }
    infile.close();
}

int main(int argc, char* argv[]){
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <file> <capacity>" << endl;
        return 1;
    }
    string file = argv[1];
    int capacity = stoi(argv[2]);
    Graph graph;    
    map<int,int> demand;
    vector<tuple<int, int , int>> edges;
    vector<int> places;
    ReadGraph(file, demand, edges, places, graph);
    cout << "Local: "  << places.size() << endl;
    vector<vector<int>> routes = GenerateAllCombinations(places, demand, capacity, graph);
    cout << "Routes: " << routes.size() << endl;
    int bestCost = INT_MAX;
    vector<vector<int>> currentCombination;
    vector<vector<int>> bestCombination;
    FindBestCombination(routes, currentCombination, 0, places, bestCost, bestCombination, graph);
    cout << "Best route combination:" << endl;
    for (const auto& route : bestCombination) {
        cout << "{ ";
        for (int city : route) {
            cout << city << " ";
        }
        cout << "} with cost: " << graph.calculateRouteCost(route) << endl;
    }
    cout << "Smallest cost: " << bestCost << endl;
    return 0;
}
