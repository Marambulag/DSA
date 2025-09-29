#include "Menu.hpp"
#include <algorithm>

namespace {
    template <typename T>
    T lerp(const T& a, const T& b, float t) { return a + (b - a) * t; }
}

Menu::Menu() {}

Menu::Menu(const sf::Font& f, const std::vector<std::string>& items, sf::Vector2f pos, float w)
    : font(&f), items(items), position(pos), width(w) {
    rebuildTexts();
    rebuildShapes();
}

void Menu::setItems(const std::vector<std::string>& newItems) {
    items = newItems;
    if (selectedIndex >= items.size()) selectedIndex = 0;
    rebuildTexts();
    rebuildShapes();
}

void Menu::setPosition(sf::Vector2f pos) {
    position = pos;
    rebuildShapes();
}

void Menu::setWidth(float w) {
    width = w;
    rebuildShapes();
}

void Menu::setStyle(const Style& s) {
    style = s;
    rebuildTexts();
    rebuildShapes();
}

bool Menu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    activated = false;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (selectedIndex == 0) selectedIndex = items.empty() ? 0 : items.size() - 1;
            else --selectedIndex;
            targetHighlightY = computeItemTop(selectedIndex);
        } else if (event.key.code == sf::Keyboard::Down) {
            if (items.empty()) selectedIndex = 0; else selectedIndex = (selectedIndex + 1) % items.size();
            targetHighlightY = computeItemTop(selectedIndex);
        } else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Return) {
            activated = true;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        auto mpos = sf::Vector2f(sf::Mouse::getPosition(window));
        // hit test items
        for (size_t i = 0; i < texts.size(); ++i) {
            auto bounds = texts[i].getGlobalBounds();
            if (bounds.contains(mpos)) {
                if (selectedIndex != i) {
                    selectedIndex = i;
                    targetHighlightY = computeItemTop(selectedIndex);
                }
            }
        }
    } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        auto mpos = sf::Vector2f(sf::Mouse::getPosition(window));
        for (size_t i = 0; i < texts.size(); ++i) {
            auto bounds = texts[i].getGlobalBounds();
            if (bounds.contains(mpos)) {
                selectedIndex = i;
                targetHighlightY = computeItemTop(selectedIndex);
                activated = true;
                break;
            }
        }
    }
    return activated;
}

void Menu::update(float dt) {
    // Smoothly animate highlight Y position
    currentHighlightY = lerp(currentHighlightY, targetHighlightY, std::clamp(style.lerpSpeed * dt, 0.f, 1.f));
    highlight.setPosition(position.x + style.padding, currentHighlightY);

    // Apply hover scale for selected item
    for (size_t i = 0; i < texts.size(); ++i) {
        bool isSel = (i == selectedIndex);
        texts[i].setFillColor(isSel ? style.itemColor : style.itemInactiveColor);
        texts[i].setScale(isSel ? style.hoverScale : 1.f, isSel ? style.hoverScale : 1.f);
    }
}

void Menu::draw(sf::RenderTarget& target) const {
    // Panel and shadow
    target.draw(shadow);
    target.draw(panel);

    // Highlight under selected
    if (!items.empty()) target.draw(highlight);

    // Text items
    for (const auto& t : texts) target.draw(t);
}

void Menu::setTitle(const std::string& title) {
    if (!font) return;
    if (texts.empty()) return;
    // Put a bold-ish title above by reusing first text size
    sf::Text titleText;
    titleText.setFont(*font);
    titleText.setString(title);
    titleText.setCharacterSize(style.itemSize + 4);
    titleText.setFillColor(style.itemColor);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(position.x + style.padding, position.y + style.padding - (style.itemSize + 10));
}

float Menu::computeItemTop(size_t index) const {
    return position.y + style.padding + index * (style.itemSize + style.itemSpacing);
}

float Menu::computeContentHeight() const {
    if (items.empty()) return 0.f;
    return items.size() * style.itemSize + (items.size() - 1) * style.itemSpacing;
}

void Menu::rebuildTexts() {
    texts.clear();
    if (!font) return;
    float y = position.y + style.padding;
    for (const auto& s : items) {
        sf::Text t;
        t.setFont(*font);
        t.setString(s);
        t.setCharacterSize(style.itemSize);
        t.setFillColor(style.itemInactiveColor);
        t.setPosition(position.x + style.padding, y);
        texts.push_back(t);
        y += style.itemSize + style.itemSpacing;
    }
    selectedIndex = std::min(selectedIndex, items.empty() ? 0ul : items.size() - 1);
    currentHighlightY = targetHighlightY = computeItemTop(selectedIndex);
}

void Menu::rebuildShapes() {
    float contentH = computeContentHeight();
    float panelH = contentH + style.padding * 2.f;

    panel.setSize({width, panelH});
    panel.setPosition(position);
    panel.setFillColor(style.panelColor);
    panel.setOutlineColor(style.outlineColor);
    panel.setOutlineThickness(style.outlineThickness);

    shadow.setSize({width + 8.f, panelH + 8.f});
    shadow.setPosition(position + sf::Vector2f(6.f, 6.f));
    shadow.setFillColor(style.shadowColor);

    highlight.setSize({width - style.padding * 2.f, static_cast<float>(style.itemSize + 4)});
    highlight.setFillColor(style.highlightColor);
    highlight.setPosition(position.x + style.padding, computeItemTop(selectedIndex));
}
