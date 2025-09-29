#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SortingVisualizer {
public:
    SortingVisualizer(sf::RenderWindow& window, sf::Font& font);

    // Blocking call that animates sorting and returns when done or canceled
    void visualize(const std::string& algoName, std::vector<int>& arr);

    // Adjust per-step delay in milliseconds (0 = fastest)
    void setDelayMs(int ms);
    int getDelayMs() const { return delayMs; }

private:
    sf::RenderWindow& window;
    sf::Font& font;
    int delayMs = 80;           // additional delay per step (ms)
    static constexpr int kMinDelay = 0;
    static constexpr int kMaxDelay = 600;
    static constexpr int kStepDelay = 20; // change per key press

    // Drawing helpers
    void drawBars(const std::vector<int>& arr, int a = -1, int b = -1, int c = -1);
    void drawHUD(const std::string& algoName, int opCount, bool finished);
    bool tick(); // handle events and pace animation; returns false if ESC/cancel

    // Algorithms with step rendering
    bool bubble(std::vector<int>& arr);
    bool insertion(std::vector<int>& arr);
    bool selection(std::vector<int>& arr);
    bool quick(std::vector<int>& arr);
    bool merge(std::vector<int>& arr);

    // helpers
    bool quickSortImpl(std::vector<int>& arr, int l, int r, int& ops);
    void mergeImpl(std::vector<int>& arr, int l, int m, int r, int& ops);
};
