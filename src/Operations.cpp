#include "Operations.hpp"
#include "Algorithms.hpp"
#include "InputHelpers.hpp"
#include "Utils.hpp"
#include "SortingVisualizer.hpp"
#include "SearchVisualizer.hpp"
#include <algorithm>
#include <sstream>

namespace operations {
using namespace algo;
using namespace utils;
using namespace input_helpers;

void performSorting(std::vector<int>& array, sf::Text& outputText, const std::string& sortType, sf::RenderWindow& window, sf::Font& font) {
    if (array.empty()) { updateOutput("Array is empty. Please enter an array first.", outputText); return; }

    // Visualize
    SortingVisualizer vis(window, font);
    // Start a bit slower by default; can be adjusted with +/- during animation
    vis.setDelayMs(120);
    vis.visualize(sortType, array);

    // Final text
    std::ostringstream oss; oss << sortType << " Sorted Array: ";
    for (const int& v : array) oss << v << ' ';
    updateOutput(oss.str(), outputText);
}

void performLinearSearch(const std::vector<int>& array, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    if (array.empty()) { outputText.setString("Array is empty. Please enter an array first."); return; }
    int key = inputKeyInWindow(outputText, font, window); if (key == -1) return;
    // Visualize linear search
    SearchVisualizer sv(window, font);
    sv.setDelayMs(200);
    auto res = sv.visualizeLinear(array, key);
    if (res.canceled) { outputText.setString("Linear Search canceled."); return; }
    if (res.index != -1) outputText.setString("Linear Search Result: Key " + std::to_string(key) + " found at index " + std::to_string(res.index));
    else outputText.setString("Linear Search Result: Key " + std::to_string(key) + " not found.");
}

void performBinarySearch(std::vector<int>& array, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    if (array.empty()) { outputText.setString("Array is empty. Please enter an array first."); return; }
    std::sort(array.begin(), array.end());
    int key = inputKeyInWindow(outputText, font, window); if (key == -1) return;
    // Visualize binary search on sorted array
    SearchVisualizer sv(window, font);
    sv.setDelayMs(200);
    auto res = sv.visualizeBinary(array, key);
    if (res.canceled) { outputText.setString("Binary Search canceled."); return; }
    if (res.index != -1) outputText.setString("Binary Search Result: Key " + std::to_string(key) + " found at index " + std::to_string(res.index));
    else outputText.setString("Binary Search Result: Key " + std::to_string(key) + " not found.");
}
}
