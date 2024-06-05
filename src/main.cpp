#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <limits>
#include <chrono>
#include "graph_class.h"
#include "brute_force_solver.h"
#include "heuristic_solver.h"

using namespace std;
using namespace std::chrono;

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

void PrintBestCombination(const vector<vector<int>>& bestCombination, Graph& graph, int bestCost) {
    cout << "Best route combination:" << endl;
    for (const auto& route : bestCombination) {
        cout << "{ ";
        for (int city : route) {
            cout << city << " ";
        }
        cout << "} with cost: " << graph.calculateRouteCost(route) << endl;
    }
    cout << "Smallest cost: " << bestCost << endl;
}

void LogTimeToFile(const string& filename, long long duration) {
    ofstream clearfile(filename, ios::out | ios::trunc);
    clearfile.close();
    ofstream outfile(filename, ios::out | ios::app);
    if (outfile.is_open()) {
        outfile << duration << endl;
        outfile.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void SolveAndPrintSolution(const string& file, int capacity, const string& solver) {
    Graph graph;    
    map<int,int> demand;
    vector<tuple<int, int , int>> edges;
    vector<int> places;
    int bestCost = numeric_limits<int>::max();
    ReadGraph(file, demand, edges, places, graph);
    vector<vector<int>> routes;
    auto start = high_resolution_clock::now();
    if (solver == "bruteforce") {
        routes = BruteForceSolver::solve(places, demand, capacity, graph, bestCost);
    } else if (solver == "heuristic") {
        //routes = HeuristicSolver::solve(places, demand, capacity, graph, bestCost);
    } else {
        cerr << "Unknown solver: " << solver << endl;
        return;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Time taken by solver: " << duration << " ms" << endl;
    LogTimeToFile("time.txt", duration);
    PrintBestCombination(routes, graph, bestCost);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <file> <capacity> <solver>" << endl;
        cout << "Available solvers: bruteforce" << endl;
        return 1;
    }
    string file = argv[1];
    int capacity = stoi(argv[2]);
    string solver = argv[3];
    SolveAndPrintSolution(file, capacity, solver);
    return 0;
}
