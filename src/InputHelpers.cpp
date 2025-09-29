#include "InputHelpers.hpp"
#include "Utils.hpp"
#include <sstream>

namespace input_helpers {
using namespace utils;

void inputArrayInWindow(std::vector<int>& arr, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    arr.clear();
    sf::Text instructionText("Enter numbers separated by space or comma. Enter to finish, ESC to cancel.", font, 20);
    instructionText.setPosition(50, 50);

    sf::Text inputText("", font, 22);
    inputText.setPosition(50, 120);
    inputText.setFillColor(sf::Color(180, 255, 180));

    std::string userInput;
    bool inputComplete = false;
    bool canceled = false;

    sf::Clock caretClock;
    bool caretOn = true;

    while (!inputComplete && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); return; }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                canceled = true; inputComplete = true; break;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    userInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == ' ' || event.text.unicode == ',') {
                    if (!userInput.empty()) { arr.push_back(std::stoi(userInput)); userInput.clear(); }
                } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (!userInput.empty()) { arr.push_back(std::stoi(userInput)); userInput.clear(); }
                    inputComplete = true;
                } else if (event.text.unicode == 8 /* backspace */) {
                    if (!userInput.empty()) userInput.pop_back();
                }
            }
        }

        if (caretClock.getElapsedTime().asSeconds() > 0.5f) {
            caretOn = !caretOn; caretClock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(instructionText);
        inputText.setString("Input: " + userInput + (caretOn ? "_" : " "));
        window.draw(inputText);
        window.display();
    }

    if (canceled) { updateOutput("Input canceled.", outputText); return; }

    std::ostringstream oss;
    oss << "Array: ";
    for (const int& val : arr) oss << val << " ";
    updateOutput(oss.str(), outputText);
}

int inputKeyInWindow(sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    sf::Text instructionText("Enter the key to search. Enter to confirm, ESC to cancel.", font, 20);
    instructionText.setPosition(50, 50);

    sf::Text inputText("", font, 22);
    inputText.setPosition(50, 120);
    inputText.setFillColor(sf::Color(180, 220, 255));

    std::string userInput;
    bool inputComplete = false;
    bool canceled = false;
    int key = -1;

    sf::Clock caretClock;
    bool caretOn = true;

    while (!inputComplete && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); return -1; }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                canceled = true; inputComplete = true; break;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    userInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (!userInput.empty()) { key = std::stoi(userInput); inputComplete = true; }
                } else if (event.text.unicode == 8 /* backspace */) {
                    if (!userInput.empty()) userInput.pop_back();
                }
            }
        }

        if (caretClock.getElapsedTime().asSeconds() > 0.5f) {
            caretOn = !caretOn; caretClock.restart();
        }

        window.clear(sf::Color::Black);
        window.draw(instructionText);
        inputText.setString("Key: " + userInput + (caretOn ? "_" : " "));
        window.draw(inputText);
        window.display();
    }

    if (canceled) return -1;
    return key;
}
}
