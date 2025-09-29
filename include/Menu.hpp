#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    struct Style {
        sf::Color panelColor = sf::Color(20, 20, 24, 230);
        sf::Color shadowColor = sf::Color(0, 0, 0, 120);
        sf::Color itemColor = sf::Color(220, 220, 230);
        sf::Color itemInactiveColor = sf::Color(170, 170, 180);
        sf::Color highlightColor = sf::Color(70, 130, 180, 220); // steel blue
        sf::Color hoverColor = sf::Color(100, 160, 210, 240);
        sf::Color outlineColor = sf::Color(255, 255, 255, 30);
        float outlineThickness = 1.0f;
        unsigned int itemSize = 22;
        float itemSpacing = 12.0f;
        float padding = 20.0f;
        float highlightRadius = 8.0f; // corner radius approximation (for visual feel)
        float lerpSpeed = 12.0f; // animation speed
        float hoverScale = 1.06f; // scale on selected item
    };

    Menu();
    Menu(const sf::Font& font, const std::vector<std::string>& items, sf::Vector2f position, float width);

    void setItems(const std::vector<std::string>& items);
    void setPosition(sf::Vector2f position);
    void setWidth(float width);
    void setStyle(const Style& style);

    // Returns true when user activated current selection (Enter or mouse click)
    bool handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    void update(float dt);
    void draw(sf::RenderTarget& target) const;

    int getSelectedIndex() const { return static_cast<int>(selectedIndex); }
    std::string getSelectedText() const { return (selectedIndex < texts.size() ? texts[selectedIndex].getString() : ""); }

    // Optional title at the top of the panel
    void setTitle(const std::string& title);

private:
    const sf::Font* font = nullptr;
    std::vector<std::string> items;
    std::vector<sf::Text> texts;

    sf::Vector2f position{100.f, 100.f};
    float width = 360.f;
    Style style;

    // Background panel and shadow
    sf::RectangleShape panel;
    sf::RectangleShape shadow;

    // Animated highlight bar
    sf::RectangleShape highlight;
    float currentHighlightY = 0.f;
    float targetHighlightY = 0.f;

    size_t selectedIndex = 0;
    bool activated = false;

    // Layout helpers
    float computeItemTop(size_t index) const;
    float computeContentHeight() const;
    void rebuildTexts();
    void rebuildShapes();
};
