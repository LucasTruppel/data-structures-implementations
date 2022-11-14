// Copyright [2022] <Lucas Castro Truppel Machado>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

// Construtor com tamanho padrão
template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    size_ = 0;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
}

// Construtor com tamanho específico
template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    size_ = 0;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
}

// Destrutor
template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

// Adiciona um elemento no final da fila
template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    }
    end_ = (end_ + 1) % max_size_;
    contents[end_] = data;
    size_++;
}

// Remove um elemento do início da fila e o retorna
template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    T data = contents[begin_];
    begin_ = (begin_ + 1) % max_size_;
    size_--;
    return data;
}

// Consulta o elemento no final da fila
template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    return contents[end_];
}

// Limpa a fila
template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

// Consulta o tamanho da fila
template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

// Consulta o tamanho máximo da fila
template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

// Verifica se a fila está vazia e retorna um bool
template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return (size_ == 0);
}

// Verifica se a fila está cheia e retorna um bool
template<typename T>
bool structures::ArrayQueue<T>::full() {
    return (size_ == max_size_);
}