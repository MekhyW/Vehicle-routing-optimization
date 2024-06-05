#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <limits>
#include <chrono>
#include <filesystem>
#include "graph_class.h"
#include "brute_force_solver.h"
#include "heuristic_solver.h"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

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

void SolveAndLogTime(const string& file, int capacity, const string& solver, const string& output_file) {
    Graph graph;
    map<int,int> demand;
    vector<tuple<int, int , int>> edges;
    vector<int> places;
    int bestCost = numeric_limits<int>::max();
    ReadGraph(file, demand, edges, places, graph);
    vector<vector<int>> routes;
    auto start = high_resolution_clock::now();
    if (solver == "bruteforce") {
        routes = BruteForceSolver::solve(places, demand, capacity, 6, graph, bestCost);
    } else if (solver == "heuristic") {
        //routes = HeuristicSolver::solve(places, demand, capacity, 6, graph, bestCost);
    } else {
        cerr << "Unknown solver: " << solver << endl;
        return;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Time taken by solver: " << duration << " ms" << endl;
    LogTimeToFile(output_file, duration);
    PrintBestCombination(routes, graph, bestCost);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <capacity> <solver>" << endl;
        cout << "Available solvers: bruteforce, heuristic" << endl;
        return 1;
    }
    int capacity = stoi(argv[1]);
    string solver = argv[2];
    for (const auto& entry : fs::directory_iterator("input")) {
        if (entry.is_regular_file() && entry.path().filename() != ".gitkeep") {
            string input_file = entry.path().string();
            string output_file = "output/" + entry.path().filename().string() + "_time.txt";
            cout << "Solving: " << input_file << endl;
            SolveAndLogTime(input_file, capacity, solver, output_file);
        }
    }
    return 0;
}
