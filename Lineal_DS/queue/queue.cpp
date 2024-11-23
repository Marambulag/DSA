#include "queue.hpp"
#include <iostream>

Queue::Queue(int capacity) : front(0), rear(-1), size(0), capacity(capacity) {
    queueArray = new int[capacity];
}

Queue::~Queue() {
    delete[] queueArray; // Libera la memoria asignada
}

bool Queue::isEmpty() const {
    return size == 0;
}

bool Queue::isFull() const {
    return size == capacity;
}

void Queue::enqueue(int value) {
    if (isFull()) {
        std::cout << "La cola está llena, no se puede insertar " << value << std::endl;
        return;
    }
    rear = (rear + 1) % capacity; // Mueve rear circularmente
    queueArray[rear] = value;
    size++;
    std::cout << value << " añadido a la cola" << std::endl;
}

void Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "La cola está vacía" << std::endl;
        return;
    }
    std::cout << queueArray[front] << " removido del frente de la cola" << std::endl;
    front = (front + 1) % capacity; // Mueve front circularmente
    size--;
}

int Queue::frontElement() const {
    if (isEmpty()) {
        std::cout << "La cola está vacía" << std::endl;
        return -1;
    }
    return queueArray[front];
}
