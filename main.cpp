/**
* @brief Função principal que carrega o grafo e oferece ao usuário a opção de operar em modo interativo ou em lote.
 *
 * Esta função carrega o grafo a partir dos arquivos de dados, e então oferece ao usuário a opção de interagir com o sistema
 * em modo interativo ou em modo de processamento em lote.
 *
 * @note A complexidade temporal depende do modo escolhido:
 * - Modo interativo: A interação com o usuário é O(1), mas o processamento das rotas pode variar dependendo das funções chamadas.
 * - Modo em lote: Não implementado, mas seria O(n), onde n é o número de operações a serem processadas.
 */
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
