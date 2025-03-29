#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
using namespace std;
#include "Location.h"
#include "Graph.h"

// Retorna o caminho mais curto como uma lista de IDs de vértices
vector<int> getPath(Graph<Location> *graph, const int &source, const int &dest);

// Calcula o menor caminho entre dois nós no grafo
void shortestPath(Graph<Location> *graph, const int &source, const int &dest);

#endif //PATHFINDER_H
