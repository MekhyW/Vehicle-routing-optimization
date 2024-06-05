#ifndef BRUTE_FORCE_SOLVER_H
#define BRUTE_FORCE_SOLVER_H

#include <vector>
#include <map>
#include <tuple>
#include "graph_class.h"

using namespace std;

vector<vector<int>> GenerateAllCombinations(const vector<int>& places, const map<int, int>& demand, int capacity, Graph& graph);
bool VerifyCapacity(const vector<int>& route, const map<int, int>& demand, int capacity);
bool coversAllCities(const vector<vector<int>>& combination, const vector<int>& places);
void FindBestCombination(const vector<vector<int>>& routes, vector<vector<int>>& currentCombination, int index, 
                         const vector<int>& places, int& bestCost, vector<vector<int>>& bestCombination, Graph& graph);

#endif // BRUTE_FORCE_SOLVER_H
