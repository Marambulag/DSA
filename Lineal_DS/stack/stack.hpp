#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

class Stack {
private:
    struct Node {
        int data;
        Node* next;
    };
    Node* topNode;
    int maxSize;
#include "stack.hpp"

int main() {
    Stack stack(3); // Limite de stack de 3 para verificar overflow

    // Pruebas de push
    stack.push(30);
    stack.push(50);
    stack.push(70);
    stack.push(90); // Esto debería causar un overflow

    // Mostrar elemento top
    std::cout << "El elemento top: " << stack.top() << std::endl;

    // Pruebas de pop
    stack.pop();
    std::cout << "El elemento después de pop: " << stack.top() << std::endl;

    stack.pop();
    stack.pop();
    stack.pop(); // Esto debería mostrar que el stack está vacío

    return 0;
}
    int currentSize;

public:
    Stack(int maxSize = 10); // Constructor con tamaño máximo predeterminado
    ~Stack(); // Destructor para liberar memoria

    void push(int value);    // Inserta un elemento en el stack
    void pop();              // Remueve el elemento top del stack
    int top() const;         // Devuelve el elemento top sin removerlo
    bool isEmpty() const;    // Verifica si el stack está vacío
    bool isFull() const;     // Verifica si el stack está lleno
};

#endif // STACK_HPP
