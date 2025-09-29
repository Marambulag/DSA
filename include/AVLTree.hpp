#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

struct AVLNode {
    int data; AVLNode* left; AVLNode* right; int height; sf::Vector2f position;
    AVLNode(int value, sf::Vector2f pos) : data(value), left(nullptr), right(nullptr), height(1), position(pos) {}
};

class AVLTree {
private:
    AVLNode* root; sf::Vector2f rootPosition;
    int getHeight(AVLNode* node); int getBalanceFactor(AVLNode* node);
    void updatePositions(AVLNode* node, float xOffset, float yOffset, float spacing = 140.0f);
    AVLNode* rotateRight(AVLNode* y, sf::RenderWindow& window, sf::Font& font);
    AVLNode* rotateLeft(AVLNode* x, sf::RenderWindow& window, sf::Font& font);
    AVLNode* insertNode(AVLNode* node, int value, sf::RenderWindow& window, sf::Font& font, float xOffset, float yOffset);
    void drawNode(sf::RenderWindow& window, sf::Font& font, AVLNode* node, sf::Vector2f parentPosition) const;
    void animateRotation(sf::RenderWindow& window, sf::Font& font, AVLNode* node, const std::string& rotationType);
public:
    AVLTree();
    void insert(int value, sf::RenderWindow& window, sf::Font& font);
    void draw(sf::RenderWindow& window, sf::Font& font) const;
};
