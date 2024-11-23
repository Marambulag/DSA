#include "Person.hpp"
#include <iostream>

int main() {
    // Nombre del archivo de datos
    std::string filename = "people.txt";

    // Cargar datos desde el archivo
    std::vector<Person> data = loadData(filename);
    if (data.empty()) {
        // Si no se pudo cargar el archivo, salimos del programa
        return 1; 
    }

    // Número de personas en los datos
    int n = data.size();

    // Crear un grafo aleatorio con n nodos
    std::vector<std::vector<int>> graph = createGraph(n);

    // ADN objetivo a buscar
    std::string target_dna = "WVVNCEOTQT";

    // Ejecutar BFS (búsqueda en anchura)
    std::cout << "Ejecutando BFS" << std::endl;
    std::pair<Person, double> bfs_result = bfs(graph, data, target_dna); // Resultado de BFS
    Person bfs_result_person = bfs_result.first; // Persona encontrada con BFS
    double bfs_duration = bfs_result.second; // Tiempo de ejecución de BFS

    // Verificar si BFS encontró a alguien
    if (!bfs_result_person.name.empty()) {
        std::cout << "BFS  Persona encontrada: " << bfs_result_person.name << ", " 
                  << bfs_result_person.address << ", " << bfs_result_person.dna << std::endl;
    } else {
        std::cout << "BFS  Error: No se encontró ninguna persona con el ADN especificado." << std::endl;
    }
    std::cout << "BFS - Tiempo de ejecución: " << bfs_duration << " segundos" << std::endl;

    // Ejecutar DFS (búsqueda en profundidad)
    std::cout << "Ejecutando DFS" << std::endl;
    std::pair<Person, double> dfs_result = dfs(graph, data, target_dna); // Resultado de DFS
    Person dfs_result_person = dfs_result.first; // Persona encontrada con DFS
    double dfs_duration = dfs_result.second; // Tiempo de ejecución de DFS

    // Verificar si DFS encontró a alguien
    if (!dfs_result_person.name.empty()) {
        std::cout << "DFS  Persona encontrada: " << dfs_result_person.name << ", " 
                  << dfs_result_person.address << ", " << dfs_result_person.dna << std::endl;
    } else {
        std::cout << "DFS  Error: No se encontró ninguna persona con el ADN especificado." << std::endl;
    }
    std::cout << "DFS - Tiempo de ejecución: " << dfs_duration << " segundos" << std::endl;

    // Mostrar estado del grafo
    std::cout << "\nEstado del Grafo:" << std::endl;
    std::cout << "Número de nodos: " << n << std::endl;

    // Contar conexiones en el grafo
    int connections = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (graph[i][j] == 1) {
                connections++;
            }
        }
    }
    std::cout << "Conexiones aleatorias generadas: " << connections << std::endl;

    return 0; // Fin del programa
}
