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
#include "brute_force_ES_solver.h"
#include "heuristic_solver.h"
#include "openmp_solver.h"
#include "mpi_solver.h"
#include "openmp-mpi_solver.h"

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
    std::cout << "Best route combination:" << endl;
    for (const auto& route : bestCombination) {
        std::cout << "{ ";
        for (int city : route) {
            std::cout << city << " ";
        }
        std::cout << "} with cost: " << graph.calculateRouteCost(route) << endl;
    }
    std::cout << "Smallest cost: " << bestCost << endl;
}

void LogToFile(const string& filename, long long duration, const vector<vector<int>>& routes, int bestCost) {
    ofstream clearfile(filename, ios::out | ios::trunc);
    clearfile.close();
    ofstream outfile(filename, ios::out | ios::app);
    if (outfile.is_open()) {
        outfile << "Time taken by solver: " << duration << " ms" << endl;
        outfile << "Best cost: " << bestCost << endl;
        for (const auto& route : routes) {
            outfile << "Route: ";
            for (const auto& node : route) {
                outfile << node << " ";
            }
            outfile << endl;
        }
        outfile.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void SolveAndLogTime(const string& file, int capacity, int max_stops, const string& solver, const string& output_file) {
    Graph graph;
    map<int,int> demand;
    vector<tuple<int, int , int>> edges;
    vector<int> places;
    int bestCost = numeric_limits<int>::max();
    ReadGraph(file, demand, edges, places, graph);
    vector<vector<int>> routes;
    auto start = high_resolution_clock::now();
    if (solver == "bruteforce") {
        routes = BruteForceSolver::solve(places, demand, capacity, max_stops, graph, bestCost);
    } else if (solver == "bruteforce-es") {
        routes = BruteForceESSolver::solve(places, demand, capacity, max_stops, graph, bestCost);
    } else if (solver == "heuristic") {
        routes = HeuristicSolver::solve(places, demand, capacity, max_stops, graph, bestCost);
    } else if (solver == "openmp") {
        routes = OpenMPSolver::solve(places, demand, capacity, max_stops, graph, bestCost);
    } else if (solver == "openmp-mpi") {
        routes = OpenMPMPISolver::solve(places, demand, capacity, max_stops, graph, bestCost);
    } else if (solver == "mpi") {
        routes = MPISolver::solve(places, demand, capacity, max_stops, graph, bestCost);
    } else {
        cerr << "Unknown solver: " << solver << endl;
        return;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "Time taken by solver: " << duration << " ms" << endl;
    LogToFile(output_file, duration, routes, bestCost);
    PrintBestCombination(routes, graph, bestCost);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <capacity> <max_stops> <solver>" << endl;
        std::cout << "Available solvers: bruteforce, bruteforce-es, heuristic, openmp, mpi, openmp-mpi" << endl;
        return 1;
    }
    int capacity = stoi(argv[1]);
    int max_stops = stoi(argv[2]);
    string solver = argv[3];
    for (const auto& entry : fs::directory_iterator("input")) {
        if (entry.is_regular_file() && entry.path().filename() != ".gitkeep") {
            string input_file = entry.path().string();
            string output_file = "output/" + entry.path().filename().string() + "_output.txt";
            std::cout << "Solving: " << input_file << endl;
            SolveAndLogTime(input_file, capacity, max_stops, solver, output_file);
        }
    }
    return 0;
}
