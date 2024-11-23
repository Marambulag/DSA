#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>

// Estructura para representar a una persona
struct Person {
    std::string name;
    std::string address;
    std::string dna;
    std::string city;
    std::string phone;
};

// Leer datos del archivo people.txt y almacenarlos en un vector de personas
std::vector<Person> loadData(const std::string& filename) {
    std::vector<Person> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: El archivo " << filename << " no existe." << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Person p;
        std::string token;
        
        std::getline(ss, token, ',');
        p.name = token;
        std::getline(ss, token, ',');
        p.name += " " + token;  // Concatenar nombre y apellido

        std::getline(ss, p.address, ',');
        std::getline(ss, p.dna, ',');
        std::getline(ss, p.city, ',');
        std::getline(ss, p.phone);

        data.push_back(p);
    }
    file.close();
    return data;
}

// Crear el grafo usando una matriz de adyacencia
std::vector<std::vector<int>> createGraph(int n) {
    std::vector<std::vector<int>> adjacencyMatrix(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Crear conexiones aleatorias con una probabilidad del 10%
            if (rand() % 10 < 1) {
                adjacencyMatrix[i][j] = 1;
                adjacencyMatrix[j][i] = 1;
            }
        }
    }
    return adjacencyMatrix;
}

// Implementación de BFS
std::pair<Person, double> bfs(const std::vector<std::vector<int>>& graph, const std::vector<Person>& data, const std::string& target_dna) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> queue;

    // Empezar desde el nodo 0
    visited[0] = true;
    queue.push(0);

    clock_t start = clock();

    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        // Revisar si el ADN coincide
        if (data[node].dna == target_dna) {
            clock_t end = clock();
            double duration = double(end - start) / CLOCKS_PER_SEC;
            return {data[node], duration};
        }

        // Explorar los vecinos
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[node][neighbor] == 1 && !visited[neighbor]) {
                queue.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    return {Person(), duration};  // Si no se encuentra el ADN
}

// Implementación de DFS
std::pair<Person, double> dfs(const std::vector<std::vector<int>>& graph, const std::vector<Person>& data, const std::string& target_dna) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::stack<int> stack;

    // Empezar desde el nodo 0
    stack.push(0);
    visited[0] = true;

    clock_t start = clock();

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        // Revisar si el ADN coincide
        if (data[node].dna == target_dna) {
            clock_t end = clock();
            double duration = double(end - start) / CLOCKS_PER_SEC;
            return {data[node], duration};
        }

        // Explorar los vecinos
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[node][neighbor] == 1 && !visited[neighbor]) {
                stack.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    return {Person(), duration};  // Si no se encuentra el ADN
}

int main() {
    // Cargar datos desde el archivo people.txt
    std::string filename = "people.txt";
    std::vector<Person> data = loadData(filename);
    if (data.empty()) {
        return 1; // Salir si no se pudieron cargar los datos
    }

    // Configurar el grafo
    int n = data.size();
    std::vector<std::vector<int>> graph = createGraph(n);

    // ADN objetivo para buscar
    std::string target_dna = "WVVNCEOTQT";  // Ejemplo

    // Ejecutar BFS
    std::cout << "Ejecutando BFS..." << std::endl;
    std::pair<Person, double> bfs_result = bfs(graph, data, target_dna); // Guardar el resultado en un par
    Person bfs_result_person = bfs_result.first; // Obtener la persona
    double bfs_duration = bfs_result.second; // Obtener la duración

    // Mostrar resultados de BFS
    if (!bfs_result_person.name.empty()) {
        std::cout << "BFS - Persona encontrada: " << bfs_result_person.name << ", " << bfs_result_person.address << ", " << bfs_result_person.dna << std::endl;
    } else {
        std::cout << "BFS - Error: No se encontró ninguna persona con el ADN especificado." << std::endl;
    }
    std::cout << "BFS - Tiempo de ejecución: " << bfs_duration << " segundos" << std::endl;

    // Ejecutar DFS
    std::cout << "Ejecutando DFS..." << std::endl;
    std::pair<Person, double> dfs_result = dfs(graph, data, target_dna); // Guardar el resultado en un par
    Person dfs_result_person = dfs_result.first; // Obtener la persona
    double dfs_duration = dfs_result.second; // Obtener la duración

    // Mostrar resultados de DFS
    if (!dfs_result_person.name.empty()) {
        std::cout << "DFS - Persona encontrada: " << dfs_result_person.name << ", " << dfs_result_person.address << ", " << dfs_result_person.dna << std::endl;
    } else {
        std::cout << "DFS - Error: No se encontró ninguna persona con el ADN especificado." << std::endl;
    }
    std::cout << "DFS - Tiempo de ejecución: " << dfs_duration << " segundos" << std::endl;

    std::cout << "\nEstado del Grafo:" << std::endl;
    std::cout << "Número de nodos: " << n << std::endl;

    // Contar las conexiones generadas
    int connections = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (graph[i][j] == 1) {
                connections++;
            }
        }
    }
    std::cout << "Conexiones aleatorias generadas: " << connections << std::endl;

    return 0;
}
