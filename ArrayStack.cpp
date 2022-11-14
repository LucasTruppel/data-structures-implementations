// Copyright [2022] <Lucas Castro Truppel Machado>
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

// Construtor com tamanho padrão
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

// Construtor com tamanho específico
template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    // COLOQUE SEU CODIGO AQUI...
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

// Destrutor
template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

// Adiciona um elemento no topo da pilha
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        // COLOQUE SEU CODIGO AQUI...
        top_++;
        contents[top_] = data;
    }
}

// Remove o elelemento do topo da pilha e o retorna
template<typename T>
T structures::ArrayStack<T>::pop() {
    // COLOQUE SEU CODIGO AQUI...
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    }
    T temp = contents[top_];
    top_--;
    return temp;
}

// Consulta o elemento no topo da pilha
template<typename T>
T& structures::ArrayStack<T>::top() {
    // COLOQUE SEU CODIGO AQUI...
    if (empty()) {
        throw std::out_of_range("pilha vazia");
    }
    return contents[top_];
}

// Esvazia a pilha
template<typename T>
void structures::ArrayStack<T>::clear() {
    // COLOQUE SEU CODIGO AQUI...
    top_ = -1;
}

// Consulta o tamanho da pilha
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    // COLOQUE SEU CODIGO AQUI...
    return top_ + 1;
}

// Consulta o tamanho máximon da pilha
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    // COLOQUE SEU CODIGO AQUI...
    return max_size_;
}

// Verifica se a pilha está vazia e retorna um bool
template<typename T>
bool structures::ArrayStack<T>::empty() {
    // COLOQUE SEU CODIGO AQUI...
    return (top_ == -1);
}

// Verifica se a pilha está cheia e retorna um bool
template<typename T>
bool structures::ArrayStack<T>::full() {
    // COLOQUE SEU CODIGO AQUI...
    return (top_ == static_cast<int>(max_size_) -1);
}