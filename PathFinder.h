#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
using namespace std;
#include "Location.h"
#include "Graph.h"

// Retorna o caminho mais curto como uma lista de IDs de vértices
vector<int> getPath(Graph<Location> *graph, const int &source, const int &dest);

// Calcula o menor caminho entre dois nós no grafo
void shortestPath(Graph<Location> *graph, const int &source);

vector<pair<int,int>> shortestPathWalking(Graph<Location> *graph, const int &dest, const int &source, const int &max_walking);

void bestPath(Graph<Location> *graph, vector<pair<int,int>> res, int &min_time, int &index_park);

vector<pair<int,int>> alternativeShortestPathWalking(Graph<Location> *graph, const int &dest, const int &source, const int &max_walking);

#endif //PATHFINDER_H
