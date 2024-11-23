#ifndef BALANCEADOR_HPP
#define BALANCEADOR_HPP

#include <vector>

class Servidor {
public:
    int id;
    int maxPeticiones;
    int peticionesActuales;

    Servidor(int id, int maxPeticiones);
    bool recibirPeticion();
    bool estaDisponible() const;
};

class Balanceador {
private:
    std::vector<Servidor> servidores;
    std::vector<std::vector<int>> costosConexion;

public:
    Balanceador(int numServidores, int maxPeticiones);
    void mostrarCostos() const;
    void distribuirPeticion();
    void mostrarEstadoServidores() const;
};

#endif
