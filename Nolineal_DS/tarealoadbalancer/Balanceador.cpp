#include "Balanceador.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>


Servidor::Servidor(int id, int maxPeticiones)
    : id(id), maxPeticiones(maxPeticiones), peticionesActuales(0) {}

bool Servidor::recibirPeticion() {
    if (peticionesActuales < maxPeticiones) {
        peticionesActuales++;
        return true;
    }
    return false;
}

bool Servidor::estaDisponible() const {
    return peticionesActuales < maxPeticiones;
}


Balanceador::Balanceador(int numServidores, int maxPeticiones) {
    for (int i = 0; i < numServidores; i++) {
        servidores.emplace_back(i, maxPeticiones);
    }

    costosConexion.resize(numServidores, std::vector<int>(numServidores, 0));
    std::srand(std::time(0));
    for (int i = 0; i < numServidores; i++) {
        for (int j = i + 1; j < numServidores; j++) {
            int costo = std::rand() % 100 + 1;
            costosConexion[i][j] = costo;
            costosConexion[j][i] = costo;
        }
    }
}

void Balanceador::mostrarCostos() const {
    std::cout << "Matriz de costos de conexion:\n";
    for (const auto& fila : costosConexion) {
        for (int costo : fila) {
            std::cout << costo << "\t";
        }
        std::cout << "\n";
    }
}

void Balanceador::distribuirPeticion() {
    int servidorElegido = -1;
    int costoMinimo = std::numeric_limits<int>::max();

    for (size_t i = 0; i < servidores.size(); i++) {
        if (servidores[i].estaDisponible() && costosConexion[0][i] < costoMinimo) {
            servidorElegido = i;
            costoMinimo = costosConexion[0][i];
        }
    }

    if (servidorElegido != -1 && servidores[servidorElegido].recibirPeticion()) {
        std::cout << "Peticion distribuida al servidor " << servidorElegido
                  << " (Coste de conexion: " << costoMinimo << ")\n";
    } else {
        std::cout << "No hay servidores disponibles.\n";
    }
}

void Balanceador::mostrarEstadoServidores() const {
    std::cout << "Estado de los servidores:\n";
    for (const auto& servidor : servidores) {
        std::cout << "Servidor " << servidor.id << ": "
                  << servidor.peticionesActuales << "/" << servidor.maxPeticiones
                  << " peticiones\n";
    }
}
