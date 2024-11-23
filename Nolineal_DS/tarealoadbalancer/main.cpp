#include "Balanceador.hpp"
#include <iostream>

int main() {
    int numServidores, maxPeticiones;
    std::cout << "Ingrese el numero de servidores: ";
    std::cin >> numServidores;
    std::cout << "Ingrese el limite maximo de peticiones por servidor: ";
    std::cin >> maxPeticiones;

    Balanceador balanceador(numServidores, maxPeticiones);
    balanceador.mostrarCostos();

    char opcion;
    do {
        balanceador.distribuirPeticion();
        balanceador.mostrarEstadoServidores();

        std::cout << "¿Desea enviar otra peticion? (s/n): ";
        std::cin >> opcion;
    } while (opcion == 's');

    return 0;
}
