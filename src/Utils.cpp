#include "Utils.hpp"

namespace utils {
void updateOutput(const std::string& message, sf::Text& outputText) {
    outputText.setString(message);
}
}
