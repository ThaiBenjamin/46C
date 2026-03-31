#include "SinglyLinkedList.hpp"

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), n(0) {}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    while (!isEmpty()) {
        remove();
    }
}

// Copy constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), n(0) {
    Node* current = other.head;
    while (current != nullptr) {
        add(current->item); // Add each item to the new list
        current = current->next;
    }
}

// Copy assignment operator
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    if (this != &other) { // Avoid self-assignment
        clear(); // Clear the current list

        Node* current = other.head;
        while (current != nullptr) {
            add(current->item); // Add each item to the new list
            current = current->next;
        }
    }
    return *this;
}

// Helper function to clear the list
template <typename T>
void SinglyLinkedList<T>::clear() {
    while (!isEmpty()) {
        remove(); // Remove all elements
    }
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const {
    return n == 0;
}

template <typename T>
size_t SinglyLinkedList<T>::size() const {
    return n;
}

template <typename T>
void SinglyLinkedList<T>::rangeCheck(size_t index) const {
    if (index >= n) {
        throw std::out_of_range("Index out of bounds");
    }
}

template <typename T>
T SinglyLinkedList<T>::get(size_t index) const {
    // TODO: implement get
    rangeCheck(index);

    Node* currNode = head;
    for(size_t i = 0; i < index; ++i){
        currNode = currNode->next;
    }

    return currNode->item;
}

template <typename T>
void SinglyLinkedList<T>::add(const T& item) {
    Node* newNode = new Node(item, head);
    head = newNode;
    if (tail == nullptr) { // If the list was empty, update the tail
        tail = head;
    }
    ++n;
}

template <typename T>
void SinglyLinkedList<T>::add(size_t index, const T& item) {
    // TODO: implement add at index
    if(index > n){
        throw std::out_of_range("Index out of bounds");
    }
    if(index == 0){
        add(item);
        return;
    }

    Node* prevNode = head;
    for(size_t i = 0; i < index-1; ++i){
        prevNode = prevNode->next;
    }

    Node* newNode = new Node(item, prevNode->next);
    prevNode->next = newNode;

    if (prevNode == tail) {
        tail = newNode;
    }

    ++n;
}

template <typename T>
T SinglyLinkedList<T>::remove() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    Node* oldHead = head;
    T item = oldHead->item;
    head = head->next;
    if (head == nullptr) { // If the list becomes empty, update the tail
        tail = nullptr;
    }
    delete oldHead;
    --n;
    return item;
}

template <typename T>
T SinglyLinkedList<T>::remove(size_t index) {
    // TODO: implement remove at index
    rangeCheck(index);

    if(index == 0){
        return remove();
    }

    Node* prevNode = head;
    
    
    for(int i = 0; i < index-1; ++i){
        prevNode = prevNode->next;
    }

    Node* tempNode = prevNode->next;

    prevNode->next = tempNode->next;

    T new_item = tempNode->item;

    if (tempNode == tail) {
        tail = prevNode;
    }
    
    delete tempNode;
    --n;
    return new_item;
}


template <typename T>
void SinglyLinkedList<T>::addLast(const T& item) {
    // TODO:  implement addLast
    Node* newNode = new Node(item, nullptr);

    if(isEmpty()){    
        head = newNode;
        tail = head;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    
    ++n;
}

template <typename T>
T SinglyLinkedList<T>::removeLast() {
    // TODO:  implement removeLast
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }

    if(n==1){
        return remove();
    }

    Node* prevNode = head;

    while(prevNode->next != tail){
        prevNode = prevNode->next;
    }

    T removed_item = tail->item;

    delete tail;
    tail = prevNode;
    tail->next = nullptr;
    --n;
    return removed_item;
}