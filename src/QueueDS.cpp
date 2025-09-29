#include "QueueDS.hpp"

QueueDS::QueueDS() : startPosition(50, 320) {}
void QueueDS::enqueue(int value) { queue.push(value); }
void QueueDS::dequeue() { if (!queue.empty()) queue.pop(); }
void QueueDS::draw(sf::RenderWindow& window, sf::Font& font) const {
    sf::Vector2f position = startPosition; auto q = queue; while (!q.empty()) {
        sf::RectangleShape nodeShape({100, 50}); nodeShape.setPosition(position); nodeShape.setFillColor(sf::Color::White); nodeShape.setOutlineColor(sf::Color::Black); nodeShape.setOutlineThickness(2);
        sf::Text nodeText(std::to_string(q.front()), font, 20); nodeText.setFillColor(sf::Color::Black); nodeText.setPosition(position.x + 35, position.y + 10);
        window.draw(nodeShape); window.draw(nodeText);
        position.x += 120; q.pop(); }
}
