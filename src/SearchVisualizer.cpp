#include "SearchVisualizer.hpp"
#include <algorithm>
#include <thread>
#include <chrono>

namespace { template <typename T> T clamp(T v, T lo, T hi){ return std::max(lo, std::min(v, hi)); } }

SearchVisualizer::SearchVisualizer(sf::RenderWindow& w, sf::Font& f) : window(w), font(f) {}

void SearchVisualizer::setDelayMs(int ms) { delayMs = clamp(ms, kMinDelay, kMaxDelay); }

bool SearchVisualizer::tick() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) { window.close(); return false; }
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Escape) return false;
            if (e.key.code == sf::Keyboard::Add || e.key.code == sf::Keyboard::Equal) setDelayMs(delayMs + kStepDelay);
            if (e.key.code == sf::Keyboard::Subtract || e.key.code == sf::Keyboard::Hyphen) setDelayMs(delayMs - kStepDelay);
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(16 + delayMs));
    return true;
}

void SearchVisualizer::waitForDismiss() {
    // Keep frame visible until a key press or window closed/ESC
    for (;;) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) { window.close(); return; }
            if (e.type == sf::Event::KeyPressed) return; // any key including ESC
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void SearchVisualizer::drawHUD(const std::string& algo, int key, int step, bool finished, int lo, int hi, int mid, int index) {
    sf::Text t; t.setFont(font); t.setCharacterSize(18); t.setFillColor(sf::Color(230,230,240));
    std::string line = algo + (finished ? " (done)" : "") +
        "  key:" + std::to_string(key) +
        "  step:" + std::to_string(step) +
        "  speed:" + std::to_string(delayMs) + "ms  ESC cancel  [+/-] speed";
    if (algo.find("Binary") != std::string::npos) {
        line += "  lo:" + std::to_string(lo) + " hi:" + std::to_string(hi) + " mid:" + std::to_string(mid);
    }
    if (finished) {
        line += "  index:" + std::to_string(index);
    }
    t.setString(line);
    t.setPosition(10,10);
    window.draw(t);
}

void SearchVisualizer::drawBars(const std::vector<int>& arr, int current, int lo, int hi, int mid, int found) {
    window.clear(sf::Color(25,28,32));
    if (arr.empty()) return;
    int n = static_cast<int>(arr.size());
    int maxv = *std::max_element(arr.begin(), arr.end());
    maxv = std::max(maxv, 1);
    float W = static_cast<float>(window.getSize().x);
    float H = static_cast<float>(window.getSize().y) - 60.f;
    float pad = 40.f;
    float barW = std::max(2.f, (W - pad * 2) / n);
    for (int i = 0; i < n; ++i) {
        float h = (H - 20.f) * (static_cast<float>(arr[i]) / maxv);
        sf::RectangleShape r({barW - 2.f, h});
        r.setPosition(pad + i * barW, H - h + 40.f);
        sf::Color col(170, 190, 210);
        if (i == current) col = sf::Color(255, 140, 0); // current check - orange
        if (lo != -1 && hi != -1 && (i < lo || i > hi)) col = sf::Color(60, 70, 80); // out of search range dimmed
        if (i == mid) col = sf::Color(100, 200, 100); // mid - green
        if (i == found) col = sf::Color(220, 100, 180); // found - pink
        r.setFillColor(col);
        window.draw(r);
    }
}

SearchVisualizer::Result SearchVisualizer::visualizeLinear(const std::vector<int>& arr, int key) {
    int step = 0;
    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        if (!tick()) return {true, -1};
        drawBars(arr, i);
        drawHUD("Linear Search", key, step++, false);
        window.display();
        if (arr[i] == key) {
            // Show found state briefly
            drawBars(arr, i, -1, -1, -1, i);
            drawHUD("Linear Search", key, step, true, -1, -1, -1, i);
            window.display();
            waitForDismiss();
            return {false, i};
        }
    }
    drawBars(arr);
    drawHUD("Linear Search", key, step, true, -1, -1, -1, -1);
    window.display();
    waitForDismiss();
    return {false, -1};
}

SearchVisualizer::Result SearchVisualizer::visualizeBinary(const std::vector<int>& arr, int key) {
    int lo = 0, hi = static_cast<int>(arr.size()) - 1;
    int step = 0;
    while (lo <= hi) {
        if (!tick()) return {true, -1};
        int mid = lo + (hi - lo) / 2;
        drawBars(arr, -1, lo, hi, mid);
        drawHUD("Binary Search", key, step++, false, lo, hi, mid);
        window.display();
        if (arr[mid] == key) {
            drawBars(arr, -1, lo, hi, mid, mid);
            drawHUD("Binary Search", key, step, true, lo, hi, mid, mid);
            window.display();
            waitForDismiss();
            return {false, mid};
        } else if (arr[mid] < key) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    drawBars(arr);
    drawHUD("Binary Search", key, step, true, lo, hi, -1, -1);
    window.display();
    waitForDismiss();
    return {false, -1};
}
