/**
* @file commandLineMenu.h
 * @brief Declaração das funções para interação via linha de comando.
 *
 * Este arquivo contém as funções que permitem ao usuário interagir com o programa por meio de um menu de opções,
 * onde é possível realizar diferentes tipos de planejamento de rotas no grafo, como planejamento de rota independente,
 * restrita e ambientalmente amigável.
 *
 * As funções principais permitem que o usuário:
 * - Selecione o modo de operação (interativo ou em lote).
 * - Informe as localizações de origem e destino.
 * - Escolha quais vértices e arestas evitar durante o planejamento de rotas.
 *
 * @note As funções descritas neste arquivo são usadas para interagir com o usuário e processar as entradas fornecidas.
 */
#ifndef COMMANDLINEMENU_H
#define COMMANDLINEMENU_H

#include <string>
using namespace std;
#include "Graph.h"
#include "Location.h"

/**
 * @brief Solicita ao usuário as localizações de origem e destino.
 *
 * Esta função exibe mensagens ao usuário, pedindo as localizações de origem e destino para o planejamento de rotas.
 *
 * @param source A string que armazenará a localização de origem fornecida pelo usuário.
 * @param destination A string que armazenará a localização de destino fornecida pelo usuário.
 *
 * @note A complexidade temporal desta função é O(1), pois a operação é apenas uma interação simples com o usuário.
 */
void getLocation(string &source, string &destination);

/**
 * @brief Processa os vértices a serem evitados durante o planejamento da rota.
 *
 * Solicita ao usuário quais vértices ele deseja evitar no grafo. O usuário fornece uma lista de IDs de vértices.
 *
 * @param graph O grafo onde os vértices serão processados.
 * @param avoidNodes Um vetor contendo os IDs dos vértices a serem evitados.
 *
 * @note A complexidade temporal dessa função é O(n), onde n é o número de vértices a serem evitados, pois a função
 *       apenas marca os vértices no grafo.
 */
void processedNodes(Graph<Location> *graph, vector<int> avoidNodes);

/**
 * @brief Processa as arestas a serem evitadas durante o planejamento da rota.
 *
 * Solicita ao usuário as arestas que ele deseja evitar no grafo. O usuário fornece uma lista de pares de vértices
 * representando as arestas a serem evitadas.
 *
 * @param graph O grafo onde as arestas serão processadas.
 * @param avoidEdges Um vetor de pares contendo os IDs dos vértices das arestas a serem evitadas.
 *
 * @note A complexidade temporal dessa função é O(e), onde e é o número de arestas a serem evitadas.
 *       A função percorre as arestas do grafo para marcar as arestas selecionadas.
 */
void selectedEdges(Graph<Location> *graph, vector<pair<int,int>> avoidEdges);

/**
 * @brief Solicita ao usuário os vértices que ele deseja evitar durante o planejamento da rota.
 *
 * Exibe uma mensagem ao usuário para que ele forneça uma lista de vértices a serem evitados. O usuário pode digitar
 * uma lista de IDs de vértices separados por vírgula ou pressionar Enter para não evitar nenhum.
 *
 * @return Um vetor contendo os IDs dos vértices a serem evitados.
 *
 * @note A complexidade temporal desta função é O(n), onde n é o número de vértices fornecidos pelo usuário,
 *       pois a função simplesmente processa a entrada do usuário.
 */
vector<int> get_avoiding_nodes();

/**
 * @brief Solicita ao usuário as arestas que ele deseja evitar durante o planejamento da rota.
 *
 * Exibe uma mensagem ao usuário para que ele forneça uma lista de arestas a serem evitadas. O usuário pode digitar
 * uma lista de arestas no formato "(vértice1, vértice2)" separadas por vírgula ou pressionar Enter para não evitar
 * nenhuma aresta.
 *
 * @return Um vetor de pares de inteiros representando as arestas a serem evitadas, onde cada par é composto por
 *         os IDs dos vértices conectados pela aresta.
 *
 * @note A complexidade temporal dessa função é O(m), onde m é o número de arestas fornecidas pelo usuário.
 *       A função processa a entrada do usuário e converte as strings em inteiros.
 */
vector <pair<int,int>> get_avoiding_edges();

/**
 * @brief Solicita ao usuário um vértice para passar durante o planejamento da rota.
 *
 * Exibe uma mensagem ao usuário pedindo o ID de um vértice que ele deseja obrigatoriamente passar durante o planejamento
 * da rota. Se o usuário não deseja passar por nenhum vértice, ele pode pressionar Enter.
 *
 * @return O ID do vértice a ser incluído no caminho ou 0 caso o usuário não queira incluir nenhum vértice.
 *
 * @note A complexidade temporal dessa função é O(1), pois é apenas uma interação simples com o usuário.
 */
int get_included_node();


/**
 * @brief Exibe o menu de opções e permite ao usuário interagir com o sistema para selecionar um tipo de planejamento de rota.
 *
 * Esta função oferece ao usuário um menu interativo com as opções de planejamento de rotas, permitindo selecionar entre
 * diferentes modos, como o planejamento de rotas independentes, rotas restritas e rotas ambientalmente amigáveis.
 * Após a seleção, o usuário fornece as informações necessárias para calcular a rota, como as localizações de origem e destino.
 *
 * @param graph O grafo contendo as localizações e distâncias.
 */
void command_line(Graph<Location> *graph);


#endif //COMMANDLINEMENU_H
