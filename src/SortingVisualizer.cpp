#include "SortingVisualizer.hpp"
#include <algorithm>
#include <thread>
#include <chrono>

namespace {
    template <typename T> T clamp(T v, T lo, T hi) { return std::max(lo, std::min(v, hi)); }
}

SortingVisualizer::SortingVisualizer(sf::RenderWindow& w, sf::Font& f) : window(w), font(f) {}

void SortingVisualizer::setDelayMs(int ms) {
    delayMs = clamp(ms, kMinDelay, kMaxDelay);
}

bool SortingVisualizer::tick() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) { window.close(); return false; }
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Escape) return false;
            if (e.key.code == sf::Keyboard::Add || e.key.code == sf::Keyboard::Equal) { // + key
                setDelayMs(delayMs + kStepDelay);
            }
            if (e.key.code == sf::Keyboard::Subtract || e.key.code == sf::Keyboard::Hyphen) { // - key
                setDelayMs(delayMs - kStepDelay);
            }
        }
    }
    // Base frame pacing (~60 fps) plus additional per-step delay for clarity
    std::this_thread::sleep_for(std::chrono::milliseconds(16 + delayMs));
    return true;
}

void SortingVisualizer::drawHUD(const std::string& algoName, int ops, bool finished) {
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(18);
    t.setFillColor(sf::Color(230, 230, 240));
    std::string info = algoName + (finished ? " (done)" : "") +
        "  ops: " + std::to_string(ops) +
        "   ESC cancel  [+/-] speed: " + std::to_string(delayMs) + "ms";
    t.setString(info);
    t.setPosition(10, 10);
    window.draw(t);
}

void SortingVisualizer::drawBars(const std::vector<int>& arr, int a, int b, int c) {
    window.clear(sf::Color(25, 28, 32));

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
        sf::Color col(180, 200, 220);
        if (i == a) col = sf::Color(255, 140, 0);      // orange
        else if (i == b) col = sf::Color(100, 200, 100); // green
        else if (i == c) col = sf::Color(220, 100, 180); // pink
        r.setFillColor(col);
        window.draw(r);
    }
}

void SortingVisualizer::visualize(const std::string& algoName, std::vector<int>& arr) {
    if (algoName == "Bubble") bubble(arr);
    else if (algoName == "Insertion") insertion(arr);
    else if (algoName == "Selection") selection(arr);
    else if (algoName == "Quick") quick(arr);
    else if (algoName == "Merge") merge(arr);
}

bool SortingVisualizer::bubble(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    int ops = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!tick()) return false;
            drawBars(arr, j, j + 1);
            drawHUD("Bubble Sort", ops, false);
            window.display();
            if (arr[j] > arr[j + 1]) { std::swap(arr[j], arr[j + 1]); ++ops; }
        }
    }
    drawBars(arr);
    drawHUD("Bubble Sort", ops, true);
    window.display();
    return true;
}

bool SortingVisualizer::insertion(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    int ops = 0;
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            if (!tick()) return false;
            arr[j + 1] = arr[j]; --j; ++ops;
            drawBars(arr, j + 1, i);
            drawHUD("Insertion Sort", ops, false);
            window.display();
        }
        arr[j + 1] = key; ++ops;
        drawBars(arr, j + 1);
        drawHUD("Insertion Sort", ops, false);
        window.display();
    }
    drawBars(arr);
    drawHUD("Insertion Sort", ops, true);
    window.display();
    return true;
}

bool SortingVisualizer::selection(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    int ops = 0;
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (!tick()) return false;
            if (arr[j] < arr[minIdx]) minIdx = j;
            drawBars(arr, minIdx, j);
            drawHUD("Selection Sort", ops, false);
            window.display();
        }
        if (minIdx != i) { std::swap(arr[i], arr[minIdx]); ++ops; }
        drawBars(arr, i);
        drawHUD("Selection Sort", ops, false);
        window.display();
    }
    drawBars(arr);
    drawHUD("Selection Sort", ops, true);
    window.display();
    return true;
}

bool SortingVisualizer::quick(std::vector<int>& arr) {
    int ops = 0;
    bool ok = quickSortImpl(arr, 0, static_cast<int>(arr.size()) - 1, ops);
    drawBars(arr);
    drawHUD("Quick Sort", ops, true);
    window.display();
    return ok;
}

bool SortingVisualizer::merge(std::vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    int ops = 0;
    // top-down merge sort
    std::function<void(int,int)> ms = [&](int l, int r){
        if (l >= r) return;
        int m = l + (r - l) / 2;
        ms(l, m); ms(m + 1, r);
        mergeImpl(arr, l, m, r, ops);
        drawBars(arr, l, m, r);
        drawHUD("Merge Sort", ops, false);
        window.display();
        tick();
    };
    ms(0, n - 1);
    drawBars(arr);
    drawHUD("Merge Sort", ops, true);
    window.display();
    return true;
}

bool SortingVisualizer::quickSortImpl(std::vector<int>& arr, int l, int r, int& ops) {
    if (l >= r) return true;
    int i = l, j = r, pivot = arr[l + (r - l) / 2];
    while (i <= j) {
        while (arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i <= j) {
            if (!tick()) return false;
            std::swap(arr[i], arr[j]); ++ops;
            drawBars(arr, i, j);
            drawHUD("Quick Sort", ops, false);
            window.display();
            ++i; --j;
        }
    }
    if (!quickSortImpl(arr, l, j, ops)) return false;
    if (!quickSortImpl(arr, i, r, ops)) return false;
    return true;
}

void SortingVisualizer::mergeImpl(std::vector<int>& arr, int l, int m, int r, int& ops) {
    int n1 = m - l + 1, n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
        ++ops;
    }
    while (i < n1) { arr[k++] = L[i++]; ++ops; }
    while (j < n2) { arr[k++] = R[j++]; ++ops; }
}
