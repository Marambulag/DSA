#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

struct Edge { int to; int weight; };

class Graph {
private:
    std::map<int, std::vector<Edge>> adjList;
    std::map<int, sf::Vector2f> nodePositions;
    std::map<int, sf::CircleShape> nodes;
    sf::Font font; std::string currentStatus; std::map<int,int> distances;
    void setupGraph();
    bool isInPath(int from, int to, const std::vector<int>& path);
    std::vector<int> reconstructPath(const std::map<int,int>& prev, int start, int end);
    void updateVisualization(sf::RenderWindow& window, const std::vector<int>& path, bool finalPath=false);
public:
    Graph();
    const sf::Font& getFont() const;
    void addNode(int id, sf::Vector2f pos);
    void addEdge(int from, int to, int weight);
    void draw(sf::RenderWindow& window, const std::vector<int>& path = {}, bool finalPath = false);
    std::vector<int> dijkstra(int start, int end, sf::RenderWindow& window);
};
