/**
* @file DataLoader.h
 * @brief Declaração das funções para carregar dados do grafo a partir de arquivos CSV.
 *
 * Contém a função `loadGraphData`, que carrega os dados dos arquivos CSV para construir o grafo
 * com vértices e arestas representando as localizações e distâncias.
 */
#ifndef DATALOADER_H
#define DATALOADER_H
#include "Graph.h"
#include "Location.h"

/**
 * @brief Carrega os dados do grafo a partir de arquivos CSV.
 *
 * A função carrega as localizações e distâncias dos arquivos `my_locations.csv` e `my_distances.csv`
 * e constrói o grafo correspondente.
 *
 * @param graph O grafo onde os dados serão carregados.
 */
void loadGraphData(Graph<Location> &graph);  // Declaração da função

#endif //DATALOADER_H
