 /**
* @file PathFinder.h
* @brief Declaração das funções de planejamento de rotas.
*
* Contém as funções necessárias para calcular o caminho mais curto e os caminhos a pé,
* além de determinar as melhores alternativas para o planejamento de rotas.
*/

#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
using namespace std;
#include "Location.h"
#include "Graph.h"



/**
 * @brief Obtém o caminho mais curto entre o nó de origem e o nó de destino no grafo.
 *
 * A função recupera o caminho mais curto, se existir, a partir do nó de origem até o nó de destino
 * após a execução de um algoritmo de busca, como o Dijkstra. Ela percorre os vértices a partir do nó de destino
 * até o nó de origem utilizando os ponteiros de caminho (`path`) armazenados durante a execução do algoritmo.
 *
 * @param graph O grafo contendo os vértices e as arestas.
 * @param source O índice do nó de origem.
 * @param dest O índice do nó de destino.
 *
 * @return Um vetor de inteiros contendo o caminho dos nós a serem percorridos, na ordem do destino até a origem.
 *
 * @note A complexidade temporal desta função é O(V), onde V é o número de vértices no caminho,
 * pois percorre os vértices a partir do destino até a origem utilizando os ponteiros de caminho.
 */
vector<int> getPath(Graph<Location> *graph, const int &source, const int &dest);

/**
 * @brief Calcula o caminho mais curto entre um nó de origem e um nó de destino no grafo.
 *
 * @param graph O grafo contendo os vértices e as arestas.
 * @param source O índice do nó de origem.
 *
 * @note A complexidade temporal deste algoritmo é O(E log V), onde E é o número de arestas e V é o número de vértices.
 */
void shortestPath(Graph<Location> *graph, const int &source);

/**
 * @brief Obtém o caminho mais curto para pedestres entre o nó de origem e o nó de destino.
 *
 * @param graph O grafo contendo os vértices e as arestas.
 * @param dest O índice do nó de destino.
 * @param source O índice do nó de origem.
 * @param max_walking O tempo máximo permitido para caminhada.
 *
 * @return Um vetor de pares de inteiros, representando os nós de estacionamento e seus respectivos tempos de caminhada.
 *
 * @note A complexidade temporal deste algoritmo é O(E log V), onde E é o número de arestas e V é o número de vértices.
 */
vector<pair<int,int>> shortestPathWalking(Graph<Location> *graph, const int &dest, const int &source, const int &max_walking);

/**
 * @brief Processa a melhor alternativa de caminho, levando em consideração o tempo de caminhada.
 *
 * @param graph O grafo contendo os vértices e as arestas.
 * @param res O vetor de resultados contendo os caminhos e tempos de caminhada.
 * @param min_time A variável que armazenará o menor tempo encontrado.
 * @param index_park O índice do estacionamento encontrado no caminho.
 * @param walking_time O tempo de caminhada específico para ser evitado.
 *
 * @note A complexidade temporal é O(n), onde n é o número de alternativas de caminhos.
 */
void bestPath(Graph<Location> *graph, vector<pair<int,int>> res, int &min_time, int &index_park);

vector<pair<int,int>> alternativeShortestPathWalking(Graph<Location> *graph, const int &dest, const int &source, const int &max_walking);

#endif //PATHFINDER_H
