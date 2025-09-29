#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace operations {
void performSorting(std::vector<int>& array, sf::Text& outputText, const std::string& sortType, sf::RenderWindow& window, sf::Font& font);
void performLinearSearch(const std::vector<int>& array, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window);
void performBinarySearch(std::vector<int>& array, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window);
}
