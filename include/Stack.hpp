#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Stack {
private:
    std::vector<int> stack;
    sf::Vector2f startPosition;
public:
    Stack();
    void push(int value);
    void pop();
    void draw(sf::RenderWindow& window, sf::Font& font) const;
};
