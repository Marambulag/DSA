#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Maze {
public:
    Maze(int width, int height, int cellSize);
    void generateMaze();
    // Depth-First Search solve (animated)
    bool solveMaze(sf::RenderWindow& window); // alias for DFS
    bool solveMazeDFS(sf::RenderWindow& window) { return solveMaze(window); }
    bool solveMazeBFS(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    // Clear VISITED/SOLUTION cells to PATH, keep START/END
    void resetTraversal();
private:
    enum Cell { WALL, PATH, VISITED, START, END, SOLUTION };
    struct Position { int x, y; Position(int x,int y):x(x),y(y){} };

    int width, height, cellSize;
    std::vector<std::vector<Cell>> grid;
    Position start, end;

    void generateDFS(Position pos);
    bool solveDFS(Position pos, sf::RenderWindow& window);
    void generatePrim();
};
