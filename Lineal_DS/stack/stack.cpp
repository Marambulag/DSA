#include "stack.hpp"

Stack::Stack(int maxSize) : topNode(nullptr), maxSize(maxSize), currentSize(0) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(int value) {
    if (isFull()) {
        std::cout << "Stack overflow: no se puede insertar " << value << std::endl;
        return;
    }
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = topNode;
    topNode = newNode;
    currentSize++;
}

void Stack::pop() {
    if (isEmpty()) {
        std::cout << "El stack está vacío" << std::endl;
        return;
    }
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
    currentSize--;
}

int Stack::top() const {
    if (isEmpty()) {
        std::cout << "El stack está vacío" << std::endl;
        return -1; // Valor de error
    }
    return topNode->data;
}

bool Stack::isEmpty() const {
    return topNode == nullptr;
}

bool Stack::isFull() const {
    return currentSize == maxSize;
}
