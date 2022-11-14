//! Copyright [2022] <Lucas Castro Truppel Machado>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {
//! ...
template<typename T>
class LinkedList {
 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    Node* at_pointer(std::size_t index);  // acessar o ponteiro de uma posição
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    T pop_pointer(Node* prev);  // retirar elemento usando ponteiro do anterior
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

// Construtor
template<typename T>
structures::LinkedList<T>::LinkedList() {
}

// Destrutor
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

// Limpa a lista
template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

// Insere um dado no fim da lista
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
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
    }
    tail = novo;
    size_++;
}

// Insere um dado no início da lista
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
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
    }
    head = novo;
    size_++;
}

// Insere um dado em uma posição específica da lista
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
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
        novo->next(prev_node->next());
        prev_node->next(novo);
        size_++;
    }
}

// Insere um dado na lista de forma ordenada
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
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

// Acessa o dado de uma posição específica
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    Node* current_node = head;
    for (std::size_t i = 0; i < index; i++) {
        current_node = current_node->next();
    }
    return current_node->data();
}

// Acessa o ponteiro para uma posição específica
template<typename T>
typename structures::LinkedList<T>::Node*
structures::LinkedList<T>::at_pointer(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("invalid index");
    }
    Node* current_node = head;
    for (std::size_t i = 0; i < index; i++) {
        current_node = current_node->next();
    }
    return current_node;
}

// Retira um elemento de uma posição específica
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
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
        Node* prev = at_pointer(index - 1);
        Node* current = prev->next();
        data = current->data();
        prev->next(current->next());
        delete current;
        size_--;
    }
    return data;
}

// Retira o último elemento da lista
template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    T data;
    if (size_ == 1) {
        Node* current = tail;
        head = nullptr;
        tail = nullptr;
        data = current->data();
        delete current;
    } else {
        Node* prev = at_pointer(size_-2);
        Node* current = prev->next();
        prev->next(nullptr);
        tail = prev;
        data = current->data();
        delete current;
    }
    size_--;
    return data;
}

// Retira o primeiro elemento da lista
template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    Node* old_head = head;
    if (size_ == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = old_head->next();
    }
    T data = old_head->data();
    delete old_head;
    size_--;
    return data;
}

// Retira um elemento dado o ponteiro do elemento anterior
template<typename T>
T structures::LinkedList<T>::pop_pointer(Node* prev) {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    Node* current = prev->next();
    if (current == nullptr) {
        throw std::out_of_range("pointer is nullptr");
    }
    T data;
    if (current == head) {
        data = pop_front();
    } else if (current == tail) {
        data = pop_back();
    } else {
        prev->next(current->next());
        data = current->data();
        delete current;
        size_--;
    }
    return data;
}

// Remove um valor específico da lista na sua primeira aparição
template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("the list is empty");
    }
    Node* current = head;
    Node* prev = nullptr;
    for (std::size_t i = 0; i < size_; i++) {
        if (current->data() == data) {
            pop_pointer(prev);
            break;
        } else {
            prev = current;
            current = current->next();
        }
    }
}

// Verifica se a lista está vazia
template<typename T>
bool structures::LinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

// Verifica se a lista contém um dado
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
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

// Verifica o index da primeira aparição de um dado
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
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
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

#endif
