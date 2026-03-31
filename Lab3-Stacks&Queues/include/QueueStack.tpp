#ifndef QUEUESTACK_TPP
#define QUEUESTACK_TPP

#include <sstream> // Include this to use std::ostringstream

template <typename T>
void QueueStack<T>::push(const T& value) {
    // TODO: implement push using two Queues
    while (!q2.isEmpty()) {
        q2.dequeue();
    }
    
    q2.enqueue(value);

    while(!q1.isEmpty()){
        q2.enqueue(q1.dequeue());
    }

    std::swap(q1, q2);
}

template <typename T>
T QueueStack<T>::pop() {
    // TODO: implement pop using two Queues
    if(isEmpty()){
        throw std::underflow_error("There are no elements to remove!");
    }
    
    return q1.dequeue();
}

template <typename T>
T QueueStack<T>::peek() const {
    // TODO: implement peek using two Queues
    if(isEmpty()){
        throw std::underflow_error("There are no elements to remove!");
    }
    
    return q1.peek();  
}

template <typename T>
bool QueueStack<T>::isEmpty() const {
    // TODO: implement isEmpty using two Queues
    return q1.isEmpty();
}

template <typename T>
std::string QueueStack<T>::toString() const {
    std::ostringstream out;
    CircularArray<T> tempQueue = q1; // Make a copy of q1 to preserve its state

    while (!tempQueue.isEmpty()) {
        out << tempQueue.dequeue() << '\n'; // Dequeue elements from the copy
    }

    out << "---\n"; // Separator to indicate the bottom of the stack
    return out.str();

}

#endif // QUEUESTACK_TPP