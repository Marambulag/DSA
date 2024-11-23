#include <iostream>
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
