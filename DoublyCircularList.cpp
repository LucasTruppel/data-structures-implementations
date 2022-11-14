//! Copyright [2022] <Lucas Castro Truppel Machado>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>

namespace structures {

template<typename T>
class DoublyCircularList {
 private:
    class Node {
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

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;

 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    T pop_pointer(Node* current); // retira com um ponteiro para o nodo
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento
    Node* at_pointer(std::size_t index);  // acessar o ponteiro de uma posição

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho
};

}  // namespace structures

// Node

// Construtor padrão
template<typename T>
structures::DoublyCircularList<T>::Node::Node(const T& data) {
    data_ = data;
    prev_= nullptr;
    next_ = nullptr;
}

// Construtor com next
template<typename T>
structures::DoublyCircularList<T>::Node::Node(const T& data, Node* next) {
    data_ = data;
    prev_= nullptr;
    next_ = next;
}

// Construtor com prev e next
template<typename T>
structures::DoublyCircularList<T>::Node::Node(const T& data, Node* prev,
Node* next) {
    data_ = data;
    prev_= prev;
    next_ = next;
}

// Getter: dado
template<typename T>
T& structures::DoublyCircularList<T>::Node::data() {
    return data_;
}

// Getter const: dado
template<typename T>
const T& structures::DoublyCircularList<T>::Node::data() const {
    return data_;
}

// Getter: anterior
template<typename T>
typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::prev() {
    return prev_;
}

// Getter const: anterior
template<typename T>
const typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::prev() const {
    return prev_;
}

// Setter: anterior
template<typename T>
void structures::DoublyCircularList<T>::Node::prev(Node* node) {
    prev_ = node;
}

// Getter: próximo
template<typename T>
typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::next() {
    return next_;
}

// Getter const: próximo
template<typename T>
const typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::Node::next() const {
    return next_;
}

// Setter: próximo
template<typename T>
void structures::DoublyCircularList<T>::Node::next(Node* node) {
    next_ = node;
}

// DoublyCircularList

// Construtor
template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    size_ = 0u;
}

// Destrutor
template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

// Limpa a lista
template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

// Insere um dado no fim da lista
template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("no memory available");
    }
    if (empty()) {
        head = novo;
        novo->next(novo);
        novo->prev(novo);
    } else {
        (head->prev())->next(novo);
        novo->next(head);
        novo->prev(head->prev());
        head->prev(novo);
    }
    size_++;
}

// Insere um dado no início da lista
template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* novo;
    novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("no memory available");
    }
    if (empty()) {
        novo->next(novo);
        novo->prev(novo);
    } else {
        novo->next(head);
        novo->prev(head->prev());
        (head->prev())->next(novo);
        head->prev(novo);
    }
    head = novo;
    size_++;
}

// Insere um dado em uma posição específica
template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data, std::size_t index) {
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
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
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
T structures::DoublyCircularList<T>::pop(std::size_t index) {
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
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    T data;
    Node* old_tail = head->prev();
    if (size_ == 1) {
        head = nullptr;
    } else {
        (old_tail->prev())->next(head);
        head->prev(old_tail->prev());
    }
    data = old_tail->data();
    delete old_tail;
    size_--;
    return data;
}

// Retira o primeiro elemento da lista
template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    Node* old_head = head;
    if (size_ == 1) {
        head = nullptr;
    } else {
        head = old_head->next();
        head->prev(old_head->prev());
        (old_head->prev())->next(head);
    }
    T data = old_head->data();
    delete old_head;
    size_--;
    return data;
}

// Retira um elemento dado um ponteiro
template<typename T>
T structures::DoublyCircularList<T>::pop_pointer(Node* current) {
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
void structures::DoublyCircularList<T>::remove(const T& data) {
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
bool structures::DoublyCircularList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

// Verifica se a lista contém um dado
template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    Node* current = head;
    bool contain = false;
    for (std::size_t i = 0; i < size_; -++) {
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
T& structures::DoublyCircularList<T>::at(std::size_t index) {
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
        current_node = head->prev();
        for (std::size_t i = size_-1; i > index; i--) {
            current_node = current_node->prev();
        }
    }
    return current_node->data();
}

// Acessa o dado de uma posição específica constante
template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
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
        current_node = head->prev();
        for (std::size_t i = size_-1; i > index; i--) {
            current_node = current_node->prev();
        }
    }
    return current_node->data();
}

// Acessa o ponteiro de uma posição específica
template<typename T>
typename structures::DoublyCircularList<T>::Node*
structures::DoublyCircularList<T>::at_pointer(std::size_t index) {
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
        current_node = head->prev();
        for (std::size_t i = size_-1; i > index; i--) {
            current_node = current_node->prev();
        }
    }
    return current_node;
}

// Verifica o index da primeira aparição de um dado
template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* current = head;
    std::size_t index;
    for (index = 0; index < size_; index++) {
        if (current->data() == data) {
            break;
        }
        current = current->next();
    }
    return index;
}

// Retorna o tamanho da lista
template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

#endif