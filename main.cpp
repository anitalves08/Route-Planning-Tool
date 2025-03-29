#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#include "Graph.h"
#include "DataLoader.h"
#include "Location.h"
#include "PathFinder.h"

void getLocation(string &source, string &destination) {
  cout << "Enter your current location: ";
  cin >> source;
  cout << "Enter your destination: ";
  cin >> destination;
}
void processedNodes(Graph<Location> *graph, vector<int> avoidNodes) {
  for (int i=0;i<avoidNodes.size();i++) {
    int index = avoidNodes[i]-1;
    graph->getVertexSet()[avoidNodes[i]-1]->setProcessing(true);
  }
}
void selectedEdges(Graph<Location> *graph, vector<pair<int,int>> avoidEdges) {
  for (int i=0;i<avoidEdges.size();i++) {
    Vertex<Location> *u = graph->getVertexSet()[avoidEdges[i].first-1];
    for (auto e: u->getAdj()) {
      if (e->getDest()->getInfo().id== avoidEdges[i].second) {
        e->setSelected(true);
        e->getReverse()->setSelected(true);
      }
    }
  }
}
vector<int> get_avoiding_nodes() {
  string line, word;
  vector<int> nodes;

  cout << "What are the nodes that you wish to avoid? (Press Enter to skip)" << endl;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  getline(cin, line);
  if (line.empty()) {
    return nodes;
  }
  stringstream ss(line);
  while (getline(ss, word ,',')) {
    nodes.push_back(stoi(word));
  }
  return nodes;
}

vector <pair<int,int>> get_avoiding_edges() {
  string line, word;
  vector<pair<int,int>> edges;

  cout << "What are the edges you wish to avoid? (Press Enter to skip)" << endl;

  getline(cin, line);
  if (line.empty()) {
    return edges;
  }

  stringstream ss(line);

  getline(ss,word,'(');
  while (getline(ss, word, ')')) {
    string num1,num2;
    stringstream se(word);
    getline(se,num1,',');
    getline(se,num2,'\0');
    edges.push_back(make_pair(stoi(num1),stoi(num2)));
    getline(ss, word,'(');
  }
  return edges;
}
int get_included_node() {
  string line;
  int node;

  cout << "What node you want to pass through?(Press Enter to skip)" << endl;

  getline(cin,line);
  if (line.empty()) {
    return 0;
  }
  stringstream ss(line);
  ss >> node;
  return node;

}

int main() {
  Graph<Location> graph;
  loadGraphData(graph);
  cout << "Graph loaded with " << graph.getVertexSet().size() << " vertices." << endl;

  int choice=0;
  while (choice != 3){

    for (Vertex<Location> *v: graph.getVertexSet()) {
      v->setProcessing(false);
      for (auto e: v->getAdj()) {
        e->setSelected(false);
      }
    }

    cout << "What planning do you want to run the program?" << endl;
    cout << "1. Independent Route Planning" << endl;
    cout << "2. Restricted Route Planning" << endl;
    cout << "3. Exit" << endl;
    cin >> choice;

    string source, destination;
    if(choice == 1) {
      getLocation(source,destination);
      shortestPath(&graph,stoi(source),stoi(destination));

      vector<int> res = getPath(&graph,stoi(source),stoi(destination));
      cout << "Source: " << source << endl;
      cout << "Destination: " << destination << endl;
      cout << "BestDrivingRoute: ";
      if (res.empty()) {
        cout << "None" << endl;
        cout << "AlternativeDrivingRoute: None" << endl;
        continue;
      }
      for(int i=res.size()-2;i>=0;i--){
        cout << res[i] << ", ";
      }
      cout << "(" << res[res.size()-1] << ")" << endl;

      shortestPath(&graph,stoi(source),stoi(destination));
      res = getPath(&graph,stoi(source),stoi(destination));
      cout << "AlternativeDrivingRoute: ";
      if (res.empty()) {
        cout << "none" << endl;
      }
      else {
        for(int i=res.size()-2;i>=0;i--){
          cout << res[i] << ", ";
        }
        cout << "(" << res[res.size()-1] << ")" << endl;
      }
    }

    if (choice == 2) {
      getLocation(source,destination);
      vector<int> nodes = get_avoiding_nodes();
      if (!nodes.empty()) {
        processedNodes(&graph,nodes);
      }

      vector<pair<int,int>> edges = get_avoiding_edges();
      if (!edges.empty()) {
        selectedEdges(&graph,edges);
      }

      int in_node= get_included_node();
      if (in_node!=0) {
        shortestPath(&graph, stoi(source), in_node);
        vector<int> res1 = getPath(&graph, stoi(source), in_node);
        shortestPath(&graph,in_node, stoi(destination));
        vector<int> res2 = getPath(&graph, in_node, stoi(destination));
        cout << "RestrictedDrivingRoute: ";
        if (res1.empty() || res2.empty()) {
          cout << "None" << endl;
          continue;
        }
        for(int i=res1.size()-2;i>=0;i--) {
          cout << res1[i] << ", ";
        }
        for (int i=res2.size()-3;i>=0;i--) {
          cout << res2[i] << ", ";
        }
        cout << "(" << res1[res1.size()-1] + res2[res2.size()-1] << ")" << endl;
      }

      else {
        shortestPath(&graph, stoi(source), stoi(destination));
        vector<int> res = getPath(&graph, stoi(source), stoi(destination));
        cout << "RestrictedDrivingRoute: ";
        if (res.empty()) {
          cout << "None" << endl;
          continue;
        }
        for(int i=res.size()-2;i>=0;i--) {
          cout << res[i] << ", ";
        }
        cout << "(" << res[res.size()-1] << ")" << endl;
      }
    }

  }
  return 0;
}
