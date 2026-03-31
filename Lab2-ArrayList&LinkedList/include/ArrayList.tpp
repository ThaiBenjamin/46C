#include "ArrayList.hpp"
#include <cstring> 

template <typename T>
ArrayList<T>::ArrayList(size_t initialCapacity, size_t resizeFactor)
    : capacity(initialCapacity), count(0), resizeFactor(resizeFactor) {
    if (capacity < 1) {
        throw std::invalid_argument("Initial capacity must be at least 1");
    }
    if (resizeFactor < 1) {
        throw std::invalid_argument("Resize factor must be at least 1");
    }
    data = new T[capacity]; // Allocate the initial array
}

template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] data; // Free the allocated memory
}

// Copy constructor
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other)
    : capacity(other.capacity), count(other.count), resizeFactor(other.resizeFactor) {
    data = new T[capacity]; // Allocate new memory for the copy
    for (size_t i = 0; i < count; ++i) {
        data[i] = other.data[i]; // Copy each element
    }
}

// Copy assignment operator
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
    if (this != &other) { // Avoid self-assignment
        // Free the existing memory
        delete[] data;

        // Copy the data from the other ArrayList
        capacity = other.capacity;
        count = other.count;
        resizeFactor = other.resizeFactor;

        data = new T[capacity]; // Allocate new memory
        for (size_t i = 0; i < count; ++i) {
            data[i] = other.data[i]; // Copy each element
        }
    }
    return *this;
}

template <typename T>
bool ArrayList<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
size_t ArrayList<T>::size() const {
    return count;
}

template <typename T>
size_t ArrayList<T>::getCapacity() const {
    return capacity;
}

template <typename T>
T ArrayList<T>::get(size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
void ArrayList<T>::add(const T& item) {
    if (count == capacity) {
        expand(); // Expand the array if it's full
    }
    data[count++] = item; // Add the item and increment the count
}

template <typename T>
void ArrayList<T>::add(size_t index, const T& item) {
    // TODO: implement add at index
    if(index > count){
        throw std::out_of_range("Index out of bounds");
    }
    if(count == capacity){
        expand();
    }
    
    for(size_t i = count; i > index; --i){
        data[i] = data[i-1];
    }

    data[index] = item;
    ++count;
}

template <typename T>
T ArrayList<T>::remove() {
    if (isEmpty()) {
        throw std::out_of_range("ArrayList is empty");
    }
    T item = data[--count]; // Remove the last item
    if (count < capacity / 4) {
        shrink(); // Shrink the array if it's less than 1/4 full
    }
    return item;
}

template <typename T>
T ArrayList<T>::remove(size_t index) {
    // TODO: implement remove at index
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }

    T removedItem = data[index];

    for(size_t i = index; i < count-1; ++i){
        data[i] = data[i+1];
    }

    --count;

    if (count < capacity / 4 && capacity / resizeFactor >= 1) {
        shrink();
    }

    return removedItem;
}

template <typename T>
void ArrayList<T>::set(size_t index, const T& item) {
    if (index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    data[index] = item; // Replace the item at the specified index
}

template <typename T>
void ArrayList<T>::expand() {
    // TODO: implement expand
    T* new_data = new T[capacity*resizeFactor]; 
    for (size_t i = 0; i < count; ++i) {
        new_data[i] = data[i]; 
    }

    delete[] data;
    data = new_data;
    capacity = capacity*resizeFactor;
}

template <typename T>
void ArrayList<T>::shrink() {
    // TODO: implement shrink
    if (capacity/resizeFactor < 1) {
        return;
    }

    T* new_data = new T[capacity/resizeFactor]; 

    for (size_t i = 0; i < count; ++i) {
        new_data[i] = data[i]; 
    }

    delete[] data;
    data = new_data;
    capacity = capacity/resizeFactor;
}