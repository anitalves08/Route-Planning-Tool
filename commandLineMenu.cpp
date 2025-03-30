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

void command_line(Graph<Location> *graph){
  int choice=0;
  while (choice != 4){

    for (Vertex<Location> *v: graph->getVertexSet()) {
      v->setProcessing(false);
      for (auto e: v->getAdj()) {
        e->setSelected(false);
      }
    }

    cout << "What planning do you want to run the program?" << endl;
    cout << "1. Independent Route Planning" << endl;
    cout << "2. Restricted Route Planning" << endl;
    cout << "3. Environmentally-Friendly Route Planning" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;

    string source, destination;
    if(choice == 1) {
      getLocation(source,destination);
      shortestPath(graph,stoi(source));

      vector<int> res = getPath(graph,stoi(source),stoi(destination));
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

      shortestPath(graph,stoi(source));
      res = getPath(graph,stoi(source),stoi(destination));
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
    else if (choice == 2) {
      getLocation(source,destination);
      vector<int> nodes = get_avoiding_nodes();
      if (!nodes.empty()) {
        processedNodes(graph,nodes);
      }

      vector<pair<int,int>> edges = get_avoiding_edges();
      if (!edges.empty()) {
        selectedEdges(graph,edges);
      }

      int in_node= get_included_node();
      if (in_node!=0) {
        shortestPath(graph, stoi(source));
        vector<int> res1 = getPath(graph, stoi(source), in_node);
        shortestPath(graph,in_node);
        vector<int> res2 = getPath(graph, in_node, stoi(destination));
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
        shortestPath(graph, stoi(source));
        vector<int> res = getPath(graph, stoi(source), stoi(destination));
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
    else if (choice ==3) {
      getLocation(source,destination);
      cout << "What is the maximum time that you wish spend walking?" << endl;
      int max_walking;
      cin >> max_walking;
      vector<int> nodes = get_avoiding_nodes();
      if (!nodes.empty()) {
        processedNodes(graph,nodes);
      }

      vector<pair<int,int>> edges = get_avoiding_edges();
      if (!edges.empty()) {
        selectedEdges(graph,edges);
      }
      //vetor com os possíveis nodulos de parking (id,walking_time)
      //se o vetor for empty significa que das duas uma:
      //ou não existiam parking nodes,
      //ou existiam mas o tempo de caminhada mais curto até ao destino excedia o max_walking_time
      vector<pair<int,int>> res = shortestPathWalking(graph,stoi(destination), stoi(source), max_walking);

      if (res.empty()) {
        int min_time1 = INT_MAX, min_time2=INT_MAX;
        int id_park1, id_park2, index_park1, index_park2, walking_time1=-1;

        cout << "No suitable route was found! 2 alternative routes that approximate your requirements:" << endl;

        while (res.empty()) {
          max_walking++;
          res=alternativeShortestPathWalking(graph,stoi(destination), stoi(source), max_walking);
        }
        shortestPath(graph,stoi(source));

        bestPath(graph,res,min_time1,index_park1);

        id_park1=res[index_park1].first;

        vector<int> driving_route1 = getPath(graph, stoi(source), id_park1);
        for (Vertex<Location> *v: graph->getVertexSet()) {
          v->setProcessing(false);
          for (auto e: v->getAdj()) {
            e->setSelected(false);
          }
        }
        //CHECK

        //Buscar a segunda melhor opção
        max_walking++;
        res = alternativeShortestPathWalking(graph,stoi(destination), stoi(source), max_walking);
        while (res.empty()) {
          max_walking++;
          res=alternativeShortestPathWalking(graph,stoi(destination), stoi(source), max_walking);
        }

        shortestPath(graph,stoi(source));
        bestPath(graph,res,min_time2,index_park2);
        id_park2=res[index_park2].first;

        vector<int> driving_route2 = getPath(graph, stoi(source), id_park2);
        for (Vertex<Location> *v: graph->getVertexSet()) {
          v->setProcessing(false);
          for (auto e: v->getAdj()) {
            e->setSelected(false);
          }
        }
        if (min_time1>min_time2) {
          swap(min_time1,min_time2);
          swap(id_park1,id_park2);
          swap(driving_route1,driving_route2);
        }
        //Imprimir rota 1

        cout << "Driving Route 1: ";
        for (int i= driving_route1.size()-2;i>=0;i--) {
          cout << driving_route1[i] << ", ";
        }
        cout << "(" << driving_route1[driving_route1.size()-1] << ")" << endl;

        cout << "Parking Node 1: " << id_park1 << endl;

        shortestPathWalking(graph,stoi(destination), stoi(source), max_walking);
        vector<int> walking_route1 = getPath(graph,stoi(destination),id_park1);
        for (Vertex<Location> *v: graph->getVertexSet()) {
          v->setProcessing(false);
          for (auto e: v->getAdj()) {
            e->setSelected(false);
          }
        }
        cout << "Walking Route 1: ";
        for (int i=0 ;i <= walking_route1.size()-2;i++) {
          cout << walking_route1[i] << ", ";
        }
        cout << "(" << walking_route1[walking_route1.size()-1] << ")" << endl;
        cout << "Total Time 1: " << min_time1 << endl;
        cout << "-----------------------------"<< endl;

        //Imprimir a rota 2
        cout << "Driving Route 2: ";
        for (int i= driving_route2.size()-2;i>=0;i--) {
          cout << driving_route2[i] << ", ";
        }
        cout << "(" << driving_route2[driving_route2.size()-1] << ")" << endl;

        cout << "Parking Node 2: " << id_park2 << endl;

        shortestPathWalking(graph,stoi(destination), stoi(source), max_walking);
        vector<int> walking_route2 = getPath(graph,stoi(destination),id_park2);
        cout << "Walking Route 2: ";
        for (int i=0 ;i <= walking_route2.size()-2;i++) {
          cout << walking_route2[i] << ", ";
        }
        cout << "(" << walking_route2[walking_route2.size()-1] << ")" << endl;

        cout << "Total Time 2: " << min_time2 << endl;


      }
      else {
        int min_time = INT_MAX, index_park, id_park;
        shortestPath(graph,stoi(source));
        bestPath(graph,res,min_time,index_park);
        id_park=res[index_park].first;

        vector<int> driving_route = getPath(graph, stoi(source), id_park);
        cout << "Driving route: ";
        for (int i= driving_route.size()-2;i>=0;i--) {
          cout << driving_route[i] << ", ";
        }
        cout << "(" << driving_route[driving_route.size()-1] << ")" << endl;
        cout << "Parking Node: " << id_park << endl;
        //vai calcular o shortest path relativo ao walking para o nodulo de origem: destination
        shortestPathWalking(graph,stoi(destination), stoi(source), max_walking);
        vector<int> walking_route = getPath(graph,stoi(destination),id_park);
        cout << "Walking route: ";
        for (int i=0 ;i <= walking_route.size()-2;i++) {
          cout << walking_route[i] << ", ";
        }
        cout << "(" << walking_route[walking_route.size()-1] << ")" << endl;
        cout << "Total Time: " << min_time << endl;

      }
    }
  }
}
