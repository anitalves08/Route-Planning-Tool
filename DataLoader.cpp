#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

#include "Graph.h"
#include "Location.h"


void loadGraphData(Graph<Location> &graph) {
  ifstream file1("my_locations.csv");
  string line;
  getline(file1, line);

  while (getline(file1, line)) {
    stringstream ss(line);
    Location location;
    string id,parking;

    getline(ss, location.name,',');
    getline(ss, id , ',');
    getline(ss, location.code, ',');
    getline(ss, parking, '\0');

    location.id = stoi(id);
    location.parking = stoi(parking);

    graph.addVertex(location);
  }

  ifstream file2("my_distances.csv");
  getline(file2, line);

  while (getline(file2, line)) {
    stringstream ss(line);
    string code1, code2, driving_time;

    getline(ss, code1, ',');
    getline(ss, code2, ',');
    getline(ss, driving_time, ',');
    int w_driving;

    if (driving_time == "X") {
      w_driving = INT_MAX;
    }
    else {
      w_driving = stoi(driving_time);
    }
    Location location1, location2;
    for (Vertex<Location>* v : graph.getVertexSet()) {
      if (v->getInfo().code == code1) location1 = v->getInfo();

      if (v->getInfo().code == code2) location2 = v->getInfo();

      if (location1.code == code1 && location2.code == code2) break;

    }
    graph.addBidirectionalEdge(location1,location2,w_driving);
  }
}
