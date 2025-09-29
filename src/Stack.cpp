#include "Stack.hpp"

Stack::Stack() : startPosition(600, 0) {}
void Stack::push(int value) { stack.push_back(value); }
void Stack::pop() { if (!stack.empty()) stack.pop_back(); }
void Stack::draw(sf::RenderWindow& window, sf::Font& font) const {
    float baseY = static_cast<float>(window.getSize().y) - 40.f; // start near bottom
    float offsetY = baseY;
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        sf::RectangleShape nodeShape({100, 50}); nodeShape.setPosition(startPosition.x, offsetY - 50.f); nodeShape.setFillColor(sf::Color::White); nodeShape.setOutlineColor(sf::Color::Black); nodeShape.setOutlineThickness(2);
        sf::Text nodeText(std::to_string(*it), font, 20); nodeText.setFillColor(sf::Color::Black); nodeText.setPosition(startPosition.x + 35, offsetY - 40.f);
        window.draw(nodeShape); window.draw(nodeText); offsetY -= 60.f; }
}
