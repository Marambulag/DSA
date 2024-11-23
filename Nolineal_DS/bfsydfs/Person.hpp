#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>

// Estructura para representar a una persona
struct Person {
    std::string name;
    std::string address;
    std::string dna;
    std::string city;
    std::string phone;
};

// Leer datos del archivo people.txt y almacenarlos en un vector de personas
std::vector<Person> loadData(const std::string& filename);

// Crear el grafo usando una matriz de adyacencia
std::vector<std::vector<int>> createGraph(int n);

// Implementación de BFS
std::pair<Person, double> bfs(const std::vector<std::vector<int>>& graph, const std::vector<Person>& data, const std::string& target_dna);

// Implementación de DFS
std::pair<Person, double> dfs(const std::vector<std::vector<int>>& graph, const std::vector<Person>& data, const std::string& target_dna);

#endif // PERSON_HPP
