//
// Created by Lenovo on 30/03/2025.
//

#ifndef COMMANDLINEMENU_H
#define COMMANDLINEMENU_H

#include <string>
using namespace std;
#include "Graph.h"
#include "Location.h"

void getLocation(string &source, string &destination);

void processedNodes(Graph<Location> *graph, vector<int> avoidNodes);

void selectedEdges(Graph<Location> *graph, vector<pair<int,int>> avoidEdges);

vector<int> get_avoiding_nodes();

vector <pair<int,int>> get_avoiding_edges();

int get_included_node();

void command_line(Graph<Location> *graph);


#endif //COMMANDLINEMENU_H
