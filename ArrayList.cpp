// Copyright [2022] <Lucas Castro Truppel Machado>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

// Construtor com tamanho padrão
template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

// Construtor com tamanho específico
template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

// Destrutor
template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

// Limpa a fila
template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

// Adiciona um elemento no final da lista
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    contents[static_cast<int>(size_)] = data;
    size_++;
}

// Adiciona um elemento no início da fila
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    int posicao = static_cast<int>(size_);
    while (posicao > 0) {
        contents[posicao] = contents[posicao - 1];
        posicao--;
    }
    contents[0] = data;
    size_++;
}

// Adiciona um elemento em uma posição específica
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("index inválido");
    }
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    std::size_t posicao = size_;
    while (posicao > index) {
        contents[posicao] = contents[posicao - 1];
        posicao--;
    }
    contents[index] = data;
    size_++;
}

// Insire um elemento em ordem
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    std::size_t i = 0;
    while (i < size_ && contents[i] < data) {
        i++;
    }
    insert(data, i);
}

// Retira um elemento de um posição específica
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }
    T value = contents[index];
    while (index < size_ - 1) {
        contents[index] = contents[index + 1];
        index++;
    }
    size_--;
    return value;
}

// Retira um elemento do final da fila
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    T value = contents[size_-1];
    size_--;
    return value;
}

// Retira um elemento do início da fila
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    T value = pop(0);
    return value;
}

// Retira um elemento específico
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    for (std::size_t i = 0; i < size_; i++) {
        if (data == contents[i]) {
            pop(i);
            break;
        }
    }
}

// Testa se a lista está cheia
template<typename T>
bool structures::ArrayList<T>::full() const {
    if (size_ == max_size_) {
        return true;
    }
    return false;
}

// Testa se a lista está vazia
template<typename T>
bool structures::ArrayList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

// Testa se a lista contém um dado específico
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    for (std::size_t i = 0; i < size_; i++) {
        if (data == contents[i]) {
            return true;
        }
    }
    return false;
}

// Procura o index de um dado específico
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    for (std::size_t i = 0; i < size_; i++) {
        if (data == contents[i]) {
            return i;
        }
    }
    return size_;
}

// Retorna o tamanho da lista
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

// Retorna o tamanho máximo da lista
template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

// Retorna o elemento de uma posição em específico
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }
    return contents[index];
}

// Acesso aos elementos da lista pelo operador []
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

// Retorna como constante o elemento de uma posição em específico
template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }
    return contents[index];
}

// Acesso aos elementos como constante da lista pelo operador []
template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

#endif