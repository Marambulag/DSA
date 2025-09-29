#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

class QueueDS {
private:
    std::queue<int> queue;
    sf::Vector2f startPosition;
public:
    QueueDS();
    void enqueue(int value);
    void dequeue();
    void draw(sf::RenderWindow& window, sf::Font& font) const;
};
