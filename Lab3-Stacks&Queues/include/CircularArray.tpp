#include "CircularArray.hpp"

template <typename T>
CircularArray<T>::CircularArray(size_t initialCapacity, size_t resizeFactor)
    : ArrayList<T>(initialCapacity, resizeFactor), front(0), rear(0), full(false) {}

template <typename T>
void CircularArray<T>::enqueue(const T& item) {
    // TODO: implement enqueue
    if(isFull()){
        resize();
    }

    this->data[rear] = item;

    rear = (rear + 1) % this->getCapacity();

    this->count++;

    if(front == rear){
        full = true;
    }
    else{
        full = false;
    }

}

template <typename T>
T CircularArray<T>::dequeue() {
    // TODO: implement dequeue
    if (isEmpty()) {
        throw std::out_of_range("CircularArray is empty!");
    }

    T item = this->data[front];

    front = (front + 1) % this->getCapacity();

    this->count--;
    full = false;

    return item;
}

template <typename T>
T CircularArray<T>::peek() const {
    // TODO: implement peek
    if (isEmpty()) {
        throw std::out_of_range("CircularArray is empty!");
    }

    return this->data[front];
}

template <typename T>
bool CircularArray<T>::isEmpty() const {
    // TODO: implement isEmpty
    if(!isFull() && front == rear){
        return true;
    }

    return false;
}

template <typename T>
bool CircularArray<T>::isFull() const {
    // TODO: implement isFull
    return full;
}

template <typename T>
void CircularArray<T>::resize() {
    // TODO: implement resize
    
    size_t newCapacity = this->capacity * this->resizeFactor;
    T* newList = new T[newCapacity];

    for (size_t i = 0; i < this->count; i++) {
        newList[i] = this->data[(front + i) % this->capacity];
    }

    delete[] this->data;
    this->data = newList;
    this->capacity = newCapacity;

    front = 0;
    rear = this->count;
    full = false;
}