/**
* @file Location.h
 * @brief Declaração da estrutura Location.
 *
 * A estrutura `Location` representa uma localização no grafo, contendo informações sobre o nome, código e
 * a presença de estacionamento.
 */
#ifndef LOCATION_H
#define LOCATION_H

/**
 * @struct Location
 * @brief Representa uma localização no grafo.
 *
 * Cada objeto `Location` contém informações sobre uma localização específica,
 * como nome, id, código e a presença de estacionamento.
 */
struct Location{
    string name;
    int id;
    string code;
    int parking;

    /**
      * @brief Operador de comparação entre duas localizações.
      *
      * Compara duas localizações com base no nome, código e id.
      *
      * @param other A outra localização a ser comparada.
      * @return Retorna verdadeiro se as localizações forem iguais.
      */
    bool operator==(const Location &other) const {
        return name == other.name && code == other.code && id == other.id;
    }

};

#endif //LOCATION_H
