#pragma once
#include <SFML/Graphics.hpp>

class LinkedList {
private:
    struct Node {
        int data; Node* next; sf::Vector2f position;
        Node(int value, sf::Vector2f pos) : data(value), next(nullptr), position(pos) {}
    };
    Node* head; sf::Vector2f startPosition;
    void adjustPositions();
public:
    LinkedList();
    void insert(int value);
    void remove();
    void reverse();
    void draw(sf::RenderWindow& window, sf::Font& font) const;
};
