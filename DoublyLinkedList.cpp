//! Copyright [2022] <Lucas Castro Truppel Machado>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class DoublyLinkedList {
 private:
    class Node {  // implementar cada um dos métodos de Node
     private:
        T data_;
        Node* prev_;
        Node* next_;

     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);
        Node(const T& data, Node* prev, Node* next);

        T& data();
        const T& data() const;

        Node* prev();
        const Node* prev() const;

        void prev(Node* node);

        Node* next();
        const Node* next() const;

        void next(Node* node);
    };

 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    T pop_pointer(Node* current);
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento
    Node* at_pointer(std::size_t index);  // acessar o ponteiro de uma posição

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

// Node

// Construtor padrão
template<typename T>
structures::DoublyLinkedList<T>::Node::Node(const T& data) {
    data_ = data;
    prev_= nullptr;
    next_ = nullptr;
}

// Construtor com next
template<typename T>
structures::DoublyLinkedList<T>::Node::Node(const T& data, Node* next) {
    data_ = data;
    prev_= nullptr;
    next_ = next;
}

// Construtor com prev e next
template<typename T>
structures::DoublyLinkedList<T>::Node::Node(const T& data, Node* prev,
Node* next) {
    data_ = data;
    prev_= prev;
    next_ = next;
}

// Getter: dado
template<typename T>
T& structures::DoublyLinkedList<T>::Node::data() {
    return data_;
}

// Getter const: dado
template<typename T>
const T& structures::DoublyLinkedList<T>::Node::data() const {
    return data_;
}

// Getter: anterior
template<typename T>
typename structures::DoublyLinkedList<T>::Node*
structures::DoublyLinkedList<T>::Node::prev() {
    return prev_;
}

// Getter const: anterior
template<typename T>
const typename structures::DoublyLinkedList<T>::Node*
structures::DoublyLinkedList<T>::Node::prev() const {
    return prev_;
}

// Setter: anterior
template<typename T>
void structures::DoublyLinkedList<T>::Node::prev(Node* node) {
    prev_ = node;
}

// Getter: próximo
template<typename T>
typename structures::DoublyLinkedList<T>::Node*
structures::DoublyLinkedList<T>::Node::next() {
    return next_;
}

// Getter const: próximo
template<typename T>
const typename structures::DoublyLinkedList<T>::Node*
structures::DoublyLinkedList<T>::Node::next() const {
    return next_;
}

// Setter: próximo
template<typename T>
void structures::DoublyLinkedList<T>::Node::next(Node* node) {
    next_ = node;
}

// DoublyLinkedList

// Construtor
template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

// Destrutor
template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// Limpa a lista
template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

// Insere um dado no fim da lista
template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node* novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("no memory available");
    }
    if (empty()) {
        head = novo;
    } else {
        Node* old_tail = tail;
        old_tail->next(novo);
        novo->prev(old_tail);
    }
    tail = novo;
    size_++;
}

// Insere um dado no início da lista
template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("no memory available");
    }
    if (empty()) {
        tail = novo;
    } else {
        Node* old_head = head;
        novo->next(old_head);
        old_head->prev(novo);
    }
    head = novo;
    size_++;
}

// Insere um dado em uma posição específica da lista
template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size()) {
        throw std::out_of_range("invalid index");
    }
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* novo;
        novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("no memory available");
        }
        Node* prev_node = at_pointer(index-1);
        (prev_node->next())->prev(novo);
        novo->next(prev_node->next());
        prev_node->next(novo);
        novo->prev(prev_node);
        size_++;
    }
}

// Insere um dado na lista de forma ordenada
template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node* current_node = head;
    std::size_t index = size_;
    for (std::size_t i = 0; i < size_; i++) {
        if (current_node->data() > data) {
            index = i;
            break;
        } else {
            current_node = current_node->next();
        }
    }
    insert(data, index);
}

// Retira um elemento de uma posição específica
template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }
    T data;
    if (index == 0) {
        data = pop_front();
    } else if (index == size_ - 1) {
        data = pop_back();
    } else {
        Node* current = at_pointer(index);
        (current->prev())->next(current->next());
        (current->next())->prev(current->prev());
        data = current->data();
        delete current;
        size_--;
    }
    return data;
}

// Retira o último elemento da lista
template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    T data;
    Node* old_tail = tail;
    if (size_ == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        tail = old_tail->prev();
        tail->next(nullptr);
    }
    data = old_tail->data();
    delete old_tail;
    size_--;
    return data;
}

// Retira o primeiro elemento da lista
template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    Node* old_head = head;
    if (size_ == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = old_head->next();
        head->prev(nullptr);
    }
    T data = old_head->data();
    delete old_head;
    size_--;
    return data;
}

// Retira um elemento dado um ponteiro
template<typename T>
T structures::DoublyLinkedList<T>::pop_pointer(Node* current) {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    if (current == nullptr) {
        throw std::out_of_range("pointer is nullptr");
    }
    T data;
    if (current == head) {
        data = pop_front();
    } else if (current == tail) {
        data = pop_back();
    } else {
        (current->prev())->next(current->next());
        (current->next())->prev(current->prev());
        data = current->data();
        delete current;
        size_--;
    }
    return data;
}

// Remove um valor específico da lista na sua primeira aparição
template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    Node* current = head;
    for (std::size_t i = 0; i < size_; i++) {
        if (current->data() == data) {
            pop_pointer(current);
            break;
        } else {
            current = current->next();
        }
    }
}

// Verifica se a lista está vazia
template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

// Verifica se a lista contém um dado
template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    Node* current = head;
    bool contain = false;
    while (current != nullptr) {
        if (current->data() == data) {
            contain = true;
            break;
        }
        current = current->next();
    }
    return contain;
}

// Acessa o dado de uma posição específica
template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    Node* current_node;
    if (index < size_ / 2) {
        current_node = head;
        for (std::size_t i = 0; i < index; i++) {
            current_node = current_node->next();
        }
    } else {
        current_node = tail;
        for (std::size_t i = size_-1; i > index; i--) {
            current_node = current_node->prev();
        }
    }
    return current_node->data();
}

// Acessa o dado de uma posição específica constante
template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    if (empty() || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    Node* current_node;
    if (index < size_ / 2) {
        current_node = head;
        for (std::size_t i = 0; i < index; i++) {
            current_node = current_node->next();
        }
    } else {
        current_node = tail;
        for (std::size_t i = size_-1; i > index; i--) {
            current_node = current_node->prev();
        }
    }
    return current_node->data();
}

// Acessa o ponteiro de uma posição específica
template<typename T>
typename structures::DoublyLinkedList<T>::Node*
structures::DoublyLinkedList<T>::at_pointer(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    Node* current_node;
    if (index < size_ / 2) {
        current_node = head;
        for (std::size_t i = 0; i < index; i++) {
            current_node = current_node->next();
        }
    } else {
        current_node = tail;
        for (std::size_t i = size_-1; i > index; i--) {
            current_node = current_node->prev();
        }
    }
    return current_node;
}

// Verifica o index da primeira aparição de um dado
template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    Node* current = head;
    std::size_t index = 0;
    while (current != nullptr) {
        if (current->data() == data) {
            break;
        }
        current = current->next();
        index++;
    }
    return index;
}

// Verifica o tamanho da lista
template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}

#endif
