#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SearchVisualizer {
public:
    struct Result { bool canceled; int index; };

    SearchVisualizer(sf::RenderWindow& window, sf::Font& font);

    // Animate linear and binary search. Returns Result with cancel state and found index (-1 if not found).
    Result visualizeLinear(const std::vector<int>& arr, int key);
    Result visualizeBinary(const std::vector<int>& arr, int key);

    // Adjust per-step delay in milliseconds
    void setDelayMs(int ms);
    int getDelayMs() const { return delayMs; }

private:
    sf::RenderWindow& window;
    sf::Font& font;
    int delayMs = 180; // per-step extra delay (ms)
    static constexpr int kMinDelay = 0;
    static constexpr int kMaxDelay = 600;
    static constexpr int kStepDelay = 20;

    // Rendering helpers
    void drawBars(const std::vector<int>& arr, int current = -1, int lo = -1, int hi = -1, int mid = -1, int found = -1);
    void drawHUD(const std::string& algo, int key, int step, bool finished, int lo = -1, int hi = -1, int mid = -1, int index = -1);
    bool tick(); // handle events, +/- speed, sleep; false if ESC/closed
    void waitForDismiss(); // after finished, wait for any key or ESC
};
