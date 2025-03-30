#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Graph.h"
#include "DataLoader.h"
#include "Location.h"
#include "commandLineMenu.h"

int main() {
  Graph<Location> graph;
  loadGraphData(graph);
  cout << "Graph loaded with " << graph.getVertexSet().size() << " vertices." << endl;
  int choice;
  std::cout << "Would you like to enter data manually or process batch mode?" << std::endl;
  std::cout << "1. Interactive Mode" << std::endl;
  std::cout << "2. Batch Mode" << std::endl;
  std::cin >> choice;
  if (choice == 1) {
    string source, dest;
    command_line(&graph);
    getLocation(source,dest);
  }
  if (choice ==2) {
    //batch_mode(&graph);
  }
  return 0;
}
