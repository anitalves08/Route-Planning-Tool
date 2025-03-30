/**
* @file MutablePriorityQueue.h
 * @brief Implementação de uma fila de prioridade mutável usando heap binário, necessária para o algoritmo de Dijkstra.
 *
 * @tparam T Tipo de dado armazenado na fila de prioridade. O tipo T deve implementar o operador '<' e ter o campo 'queueIndex'.
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

/**
  * class T must have: (i) accessible field int queueIndex; (ii) operator< defined.
  */
 /**
  * @class MutablePriorityQueue
  * @brief Fila de prioridade mutável baseada em heap binário.
  *
  * Esta classe fornece as operações necessárias para o algoritmo de Dijkstra,
  * permitindo a inserção, extração do mínimo e diminuição da chave de elementos
  * na fila de prioridade.
  *
  * @tparam T Tipo de dado armazenado na fila de prioridade.
  *
 * @note A complexidade temporal das operações são as seguintes:
  * - `insert`: O(log n) onde n é o número de elementos na fila.
  * - `extractMin`: O(log n) onde n é o número de elementos na fila.
  * - `decreaseKey`: O(log n) onde n é o número de elementos na fila.
  */
template <class T>
class MutablePriorityQueue {
    std::vector<T *> H;

    /**
      * @brief Reorganiza a heap para cima, a partir do índice fornecido.
      *
      * @param i O índice do elemento a ser reorganizado.
      *
      * @note A complexidade temporal é O(log n) onde n é o número de elementos na fila.
      */
    void heapifyUp(unsigned i);

    /**
      * @brief Reorganiza a heap para baixo, a partir do índice fornecido.
      *
      * @param i O índice do elemento a ser reorganizado.
      *
      * @note A complexidade temporal é O(log n) onde n é o número de elementos na fila.
      */
    void heapifyDown(unsigned i);

    /**
      * @brief Atualiza o índice de um elemento na heap.
      *
      * @param i O índice do elemento.
      * @param x O ponteiro para o elemento.
      */
    inline void set(unsigned i, T * x);
public:
    /**
      * @brief Constrói uma nova fila de prioridade vazia.
      */
    MutablePriorityQueue();

    /**
      * @brief Insere um elemento na fila de prioridade.
      *
      * @param x O ponteiro para o elemento a ser inserido.
      *
      * @note A complexidade temporal é O(log n) onde n é o número de elementos na fila.
      */
    void insert(T * x);

    /**
      * @brief Extrai o elemento com a menor chave da fila de prioridade.
      *
      * @return O ponteiro para o elemento extraído.
      *
      * @note A complexidade temporal é O(log n) onde n é o número de elementos na fila.
      */
    T * extractMin();

    /**
      * @brief Diminui a chave de um elemento na fila de prioridade.
      *
      * @param x O ponteiro para o elemento a ter a chave diminuída.
      *
      * @note A complexidade temporal é O(log n) onde n é o número de elementos na fila.
      */
    void decreaseKey(T * x);

    /**
      * @brief Verifica se a fila de prioridade está vazia.
      *
      * @return Retorna verdadeiro se a fila estiver vazia, falso caso contrário.
      */
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */