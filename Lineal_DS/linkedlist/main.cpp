#include "linkedlist.hpp"
#include <iostream>

using namespace std;

int main() {
    LinkedList list;

    // Insertar nodos
    list.addNode(10);
    list.addNode(20);
    list.insertAtHead(5);
    list.insertAtPosition(15, 2);

    cout << "Lista después de la inserción:" << endl;
    list.showList();

    // Buscar nodos
    cout << "Buscar valor 15: " << (list.search(15) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscar valor 100: " << (list.search(100) ? "Encontrado" : "No encontrado") << endl;

    // Eliminar nodo
    list.deleteNode(10);
    cout << "Lista después de eliminar 10:" << endl;
    list.showList();

    return 0;
}