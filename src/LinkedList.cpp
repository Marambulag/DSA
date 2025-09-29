#include "LinkedList.hpp"

LinkedList::LinkedList() : head(nullptr), startPosition(50, 200) {}

void LinkedList::insert(int value) {
    Node* newNode = new Node(value, sf::Vector2f(startPosition.x, startPosition.y));
    if (!head) {
        head = newNode;
    } else {
        Node* t = head; while (t->next) t = t->next; t->next = newNode;
    }
    // Reflow positions to keep spacing consistent and on-screen
    adjustPositions();
}

void LinkedList::remove() {
    if (!head) return;
    Node* t = head; head = head->next; delete t;
    // Reflow remaining nodes
    adjustPositions();
}

void LinkedList::reverse() {
    Node *prev = nullptr, *curr = head, *next = nullptr; while (curr) { next = curr->next; curr->next = prev; prev = curr; curr = next; } head = prev; adjustPositions();
}

void LinkedList::adjustPositions() {
    Node* t = head; float x = 100; while (t) { t->position = {x, startPosition.y}; x += 120; t = t->next; }
}

void LinkedList::draw(sf::RenderWindow& window, sf::Font& font) const {
    Node* t = head; while (t) {
        sf::RectangleShape nodeShape({100, 50}); nodeShape.setPosition(t->position); nodeShape.setFillColor(sf::Color::White); nodeShape.setOutlineColor(sf::Color::Black); nodeShape.setOutlineThickness(2);
        sf::Text nodeText(std::to_string(t->data), font, 20); nodeText.setFillColor(sf::Color::Black); nodeText.setPosition(t->position.x + 35, t->position.y + 10);
        window.draw(nodeShape); window.draw(nodeText);
        if (t->next) { sf::Vertex line[] = { sf::Vertex({t->position.x + 100, t->position.y + 25}), sf::Vertex({t->next->position.x, t->next->position.y + 25}) }; window.draw(line, 2, sf::Lines); }
        t = t->next; }
}
