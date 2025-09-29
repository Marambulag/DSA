#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace input_helpers {
void inputArrayInWindow(std::vector<int>& arr, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window);
int inputKeyInWindow(sf::Text& outputText, sf::Font& font, sf::RenderWindow& window);
}
