#include <iostream>
#include "queue.hpp"

int main() {
    Queue q(3); // Capacidad fija de 3 para probar la cola circular

    // Pruebas de enqueue
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40); // Esto debería mostrar que la cola está llena

    // Mostrar el elemento al frente
    std::cout << "Elemento en el frente: " << q.frontElement() << std::endl;

    // Pruebas de dequeue
    q.dequeue();
    std::cout << "Elemento en el frente después de dequeue: " << q.frontElement() << std::endl;

    // Probar la cola circular
    q.enqueue(40);
    std::cout << "Elemento en el frente después de encolar 40: " << q.frontElement() << std::endl;

    return 0;
}
