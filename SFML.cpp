#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <map>
#include <limits>
#include <thread>
#include <chrono>
#include <random>

// Utility Functions
void updateOutput(const std::string& message, sf::Text& outputText) {
    outputText.setString(message);
}

void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        // Move elements that are greater than the key one position ahead
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        // Find the minimum element in the remaining array
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the first element
        std::swap(arr[i], arr[minIndex]);
    }
}


void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high], i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int linearSearch(const std::vector<int>& arr, int key) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int binarySearch(const std::vector<int>& arr, int key, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Input Helper Functions
void inputArrayInWindow(std::vector<int>& arr, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    arr.clear();
    sf::Text instructionText("Enter numbers separated by space. Press Enter to finish.", font, 20);
    instructionText.setPosition(50, 50);

    sf::Text inputText("", font, 20);
    inputText.setPosition(50, 120);
    inputText.setFillColor(sf::Color::Green);

    std::string userInput = "";
    bool inputComplete = false;

    while (!inputComplete && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    userInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == ' ') {
                    if (!userInput.empty()) {
                        arr.push_back(std::stoi(userInput));
                        userInput.clear();
                    }
                } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (!userInput.empty()) {
                        arr.push_back(std::stoi(userInput));
                        userInput.clear();
                    }
                    inputComplete = true;
                } else if (event.text.unicode == '\b' && !userInput.empty()) {
                    userInput.pop_back();
                }
            }

            window.clear(sf::Color::Black);
            window.draw(instructionText);
            inputText.setString("Input: " + userInput);
            window.draw(inputText);
            window.display();
        }
    }

    std::ostringstream oss;
    oss << "Array: ";
    for (const int& val : arr) oss << val << " ";
    updateOutput(oss.str(), outputText);
}

// Helper Function for Key Input
int inputKeyInWindow(sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    sf::Text instructionText("Enter the key to search. Press Enter to confirm.", font, 20);
    instructionText.setPosition(50, 50);

    sf::Text inputText("", font, 20);
    inputText.setPosition(50, 120);
    inputText.setFillColor(sf::Color::Cyan);

    std::string userInput = "";
    bool inputComplete = false;
    int key = -1;

    while (!inputComplete && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    userInput += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (!userInput.empty()) {
                        key = std::stoi(userInput);
                        inputComplete = true;
                    }
                } else if (event.text.unicode == '\b' && !userInput.empty()) {
                    userInput.pop_back();
                }
            }

            window.clear(sf::Color::Black);
            window.draw(instructionText);
            inputText.setString("Key: " + userInput);
            window.draw(inputText);
            window.display();
        }
    }

    return key;
}

// Perform Sorting
void performSorting(std::vector<int>& array, sf::Text& outputText, const std::string& sortType) {
    if (array.empty()) {
        updateOutput("Array is empty. Please enter an array first.", outputText);
        return;
    }

    if (sortType == "Bubble") bubbleSort(array);
    else if (sortType == "Insertion") insertionSort(array);
    else if (sortType == "Selection") selectionSort(array);
    else if (sortType == "Quick") quickSort(array, 0, array.size() - 1);
    else if (sortType == "Merge") mergeSort(array, 0, array.size() - 1);

    std::ostringstream oss;
    oss << sortType << " Sorted Array: ";
    for (const int& val : array) oss << val << " ";
    updateOutput(oss.str(), outputText);
}

// Perform Linear Search performLinearSearch
void performLinearSearch(const std::vector<int>& array, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    if (array.empty()) {
        outputText.setString("Array is empty. Please enter an array first.");
        return;
    }

    int key = inputKeyInWindow(outputText, font, window);
    if (key == -1) return;

    int index = linearSearch(array, key);
    if (index != -1) {
        outputText.setString("Linear Search Result: Key " + std::to_string(key) + " found at index " + std::to_string(index));
    } else {
        outputText.setString("Linear Search Result: Key " + std::to_string(key) + " not found.");
    }
}

// Perform Binary Search
void performBinarySearch(std::vector<int>& array, sf::Text& outputText, sf::Font& font, sf::RenderWindow& window) {
    if (array.empty()) {
        outputText.setString("Array is empty. Please enter an array first.");
        return;
    }

    std::sort(array.begin(), array.end());
    int key = inputKeyInWindow(outputText, font, window);
    if (key == -1) return;

    int index = binarySearch(array, key, 0, array.size() - 1);
    if (index != -1) {
        outputText.setString("Binary Search Result: Key " + std::to_string(key) + " found at index " + std::to_string(index));
    } else {
        outputText.setString("Binary Search Result: Key " + std::to_string(key) + " not found.");
    }
}


// Linked List Implementation
class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        sf::Vector2f position;

        Node(int value, sf::Vector2f pos) : data(value), next(nullptr), position(pos) {}
    };

    Node* head;
    sf::Vector2f startPosition;

public:
    LinkedList() : head(nullptr), startPosition(50, 200) {}

    void insert(int value) {
        Node* newNode = new Node(value, sf::Vector2f(startPosition.x, startPosition.y));
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            newNode->position = sf::Vector2f(temp->position.x + 120, temp->position.y);
            temp->next = newNode;
        }
    }

    void remove() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void reverse() {
        Node *prev = nullptr, *curr = head, *next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        adjustPositions();
    }

    void adjustPositions() {
        Node* temp = head;
        float offsetX = 100;
        while (temp) {
            temp->position = sf::Vector2f(offsetX, startPosition.y);
            offsetX += 120;
            temp = temp->next;
        }
    }

    void draw(sf::RenderWindow& window, sf::Font& font) const {
        Node* temp = head;
        while (temp) {
            sf::RectangleShape nodeShape(sf::Vector2f(100, 50));
            nodeShape.setPosition(temp->position);
            nodeShape.setFillColor(sf::Color::White);
            nodeShape.setOutlineColor(sf::Color::Black);
            nodeShape.setOutlineThickness(2);

            sf::Text nodeText(std::to_string(temp->data), font, 20);
            nodeText.setFillColor(sf::Color::Black);
            nodeText.setPosition(temp->position.x + 35, temp->position.y + 10);

            window.draw(nodeShape);
            window.draw(nodeText);

            if (temp->next) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(temp->position.x + 100, temp->position.y + 25)),
                    sf::Vertex(sf::Vector2f(temp->next->position.x, temp->next->position.y + 25))
                };
                window.draw(line, 2, sf::Lines);
            }

            temp = temp->next;
        }
    }
};

// Stack Implementation
// Stack Implementation
class Stack {
private:
    std::vector<int> stack;
    sf::Vector2f startPosition; // Starting position for the stack

public:
    Stack() : startPosition(600, 600) {}

    void push(int value) {
        stack.push_back(value); // Add a value to the stack
    }

    void pop() {
        if (!stack.empty()) stack.pop_back(); // Remove the top element
    }

    void draw(sf::RenderWindow& window, sf::Font& font) const {
        float offsetY = startPosition.y; // Start from the base position

        // Iterate through the stack in normal order (bottom to top)
        for (auto it = stack.begin(); it != stack.end(); ++it) {
            sf::RectangleShape nodeShape(sf::Vector2f(100, 50));
            nodeShape.setPosition(startPosition.x, offsetY); // Place element at current offset
            nodeShape.setFillColor(sf::Color::White);
            nodeShape.setOutlineColor(sf::Color::Black);
            nodeShape.setOutlineThickness(2);

            sf::Text nodeText(std::to_string(*it), font, 20);
            nodeText.setFillColor(sf::Color::Black);
            nodeText.setPosition(startPosition.x + 35, offsetY + 10);

            window.draw(nodeShape); // Draw the rectangle
            window.draw(nodeText); // Draw the value

            offsetY -= 60; // Move upward for the next element
        }
    }
};


// Queue Implementation
class Queue {
private:
    std::queue<int> queue;
    sf::Vector2f startPosition;

public:
    Queue() : startPosition(50, 200) {}

    void enqueue(int value) {
        queue.push(value);
    }

    void dequeue() {
        if (!queue.empty()) queue.pop();
    }

    void draw(sf::RenderWindow& window, sf::Font& font) const {
        sf::Vector2f position = startPosition;
        std::queue<int> tempQueue = queue;
        while (!tempQueue.empty()) {
            sf::RectangleShape nodeShape(sf::Vector2f(100, 50));
            nodeShape.setPosition(position);
            nodeShape.setFillColor(sf::Color::White);
            nodeShape.setOutlineColor(sf::Color::Black);
            nodeShape.setOutlineThickness(2);

            sf::Text nodeText(std::to_string(tempQueue.front()), font, 20);
            nodeText.setFillColor(sf::Color::Black);
            nodeText.setPosition(position.x + 35, position.y + 10);

            window.draw(nodeShape);
            window.draw(nodeText);

            position.x += 120;
            tempQueue.pop();
        }
    }
};

// AVL Node Structure
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    sf::Vector2f position;

    AVLNode(int value, sf::Vector2f pos)
        : data(value), left(nullptr), right(nullptr), height(1), position(pos) {}
};

// AVL Tree Class
class AVLTree {
private:
    AVLNode* root;
    sf::Vector2f rootPosition;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void animateMovement(sf::RenderWindow& window, sf::Font& font, AVLNode* node, const sf::Vector2f& newPosition) {
        sf::Vector2f startPos = node->position;
        int steps = 30;
        for (int i = 0; i <= steps; ++i) {
            node->position = startPos + (newPosition - startPos) * (static_cast<float>(i) / steps);
            window.clear(sf::Color::Black);
            draw(window, font);
            window.display();
            sf::sleep(sf::milliseconds(10));
        }
        node->position = newPosition;
    }

    void updatePositions(AVLNode* node, float xOffset, float yOffset, float spacing = 140.0f) {
        if (!node) return;

        node->position = rootPosition + sf::Vector2f(xOffset, yOffset);

        updatePositions(node->left, xOffset - spacing, yOffset + 80, spacing / 1.5f);
        updatePositions(node->right, xOffset + spacing, yOffset + 80, spacing / 1.5f);
    }

    AVLNode* rotateRight(AVLNode* y, sf::RenderWindow& window, sf::Font& font) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        animateRotation(window, font, y, "LL");

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        updatePositions(root, 0, 0);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x, sf::RenderWindow& window, sf::Font& font) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        animateRotation(window, font, x, "RR");

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        updatePositions(root, 0, 0);
        return y;
    }

    AVLNode* insertNode(AVLNode* node, int value, sf::RenderWindow& window, sf::Font& font, float xOffset, float yOffset) {
        if (!node) {
            return new AVLNode(value, rootPosition + sf::Vector2f(xOffset, yOffset));
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value, window, font, xOffset - 60, yOffset + 80);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value, window, font, xOffset + 60, yOffset + 80);
        } else {
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1 && value < node->left->data) {
            return rotateRight(node, window, font);
        }
        if (balanceFactor < -1 && value > node->right->data) {
            return rotateLeft(node, window, font);
        }
        if (balanceFactor > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left, window, font);
            return rotateRight(node, window, font);
        }
        if (balanceFactor < -1 && value < node->right->data) {
            node->right = rotateRight(node->right, window, font);
            return rotateLeft(node, window, font);
        }

        return node;
    }

    void drawNode(sf::RenderWindow& window, sf::Font& font, AVLNode* node, sf::Vector2f parentPosition) const {
        if (!node) return;

        if (parentPosition != sf::Vector2f(-1, -1)) {
            sf::Vertex line[] = {
                sf::Vertex(parentPosition, sf::Color::Red),
                sf::Vertex(node->position, sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
        }

        sf::CircleShape nodeShape(30);
        nodeShape.setFillColor(sf::Color::White);
        nodeShape.setOutlineColor(sf::Color::Black);
        nodeShape.setOutlineThickness(2);
        nodeShape.setPosition(node->position - sf::Vector2f(30, 30));

        sf::Text nodeText(std::to_string(node->data), font, 20);
        nodeText.setFillColor(sf::Color::Black);
        nodeText.setPosition(node->position.x - 10, node->position.y - 15);

        window.draw(nodeShape);
        window.draw(nodeText);

        drawNode(window, font, node->left, node->position);
        drawNode(window, font, node->right, node->position);
    }

    void animateRotation(sf::RenderWindow& window, sf::Font& font, AVLNode* node, const std::string& rotationType) {
        sf::Text rotationText(rotationType, font, 30);
        rotationText.setFillColor(sf::Color::Yellow);
        rotationText.setPosition(node->position.x - 50, node->position.y - 100);

        window.clear(sf::Color::Black);
        draw(window, font);
        window.draw(rotationText);
        window.display();

        sf::sleep(sf::milliseconds(1000));
    }

public:
    AVLTree() : root(nullptr), rootPosition(400, 50) {}

    void insert(int value, sf::RenderWindow& window, sf::Font& font) {
        root = insertNode(root, value, window, font, 0, 0);
        updatePositions(root, 0, 0);
    }

    void draw(sf::RenderWindow& window, sf::Font& font) const {
        drawNode(window, font, root, sf::Vector2f(-1, -1));
    }
};

struct Edge {
    int to;
    int weight;
};

class Graph {
private:
    std::map<int, std::vector<Edge>> adjList;
    std::map<int, sf::Vector2f> nodePositions;
    std::map<int, sf::CircleShape> nodes;
    sf::Font font;
    std::string currentStatus;
    std::map<int, int> distances;

    // Private method declarations
    void setupGraph() {
        // Create nodes
        addNode(1, {100, 100});   // Top left
        addNode(2, {300, 100});   // Top middle
        addNode(3, {500, 100});   // Top right
        addNode(4, {100, 300});   // Middle left
        addNode(5, {300, 300});   // Center
        addNode(6, {500, 300});   // Middle right
        addNode(7, {200, 500});   // Bottom left
        addNode(8, {400, 500});   // Bottom right

        // Add edges
        addEdge(1, 2, 4);
        addEdge(2, 3, 3);
        addEdge(1, 4, 2);
        addEdge(2, 5, 6);
        addEdge(3, 6, 2);
        addEdge(4, 5, 5);
        addEdge(5, 6, 4);
        addEdge(4, 7, 3);
        addEdge(5, 7, 8);
        addEdge(5, 8, 7);
        addEdge(6, 8, 6);
        addEdge(7, 8, 4);
    }

    bool isInPath(int from, int to, const std::vector<int>& path) {
        if (path.size() < 2) return false;
        for (size_t i = 0; i < path.size() - 1; i++) {
            if ((path[i] == from && path[i + 1] == to) ||
                (path[i] == to && path[i + 1] == from)) {
                return true;
            }
        }
        return false;
    }

    std::vector<int> reconstructPath(const std::map<int, int>& prev, int start, int end) {
        std::vector<int> path;
        for (int at = end; at != -1 && at != 0; at = prev.at(at)) {
            path.push_back(at);
            if (at == start) break;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    void updateVisualization(sf::RenderWindow& window, const std::vector<int>& path, bool finalPath = false) {
        window.clear(sf::Color::Black);
        draw(window, path, finalPath);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }

public:
    Graph() {
        if (!font.loadFromFile("DejaVuSans.ttf")) {
            throw std::runtime_error("Error loading font");
        }
        currentStatus = "Waiting to start...";
        setupGraph();
    }

    // Add this new getter method for the font
    const sf::Font& getFont() const {
        return font;
    }

    void addNode(int id, sf::Vector2f pos) {
        nodePositions[id] = pos;
        
        sf::CircleShape node(20);
        node.setPosition(pos);
        node.setFillColor(sf::Color::White);
        node.setOutlineColor(sf::Color::Black);
        node.setOutlineThickness(2);
        nodes[id] = node;
    }

    void addEdge(int from, int to, int weight) {
        adjList[from].push_back({to, weight});
        adjList[to].push_back({from, weight}); // Undirected graph
    }

    void draw(sf::RenderWindow& window, const std::vector<int>& path = {}, bool finalPath = false) {
        // Draw edges
        for (const auto& pair : adjList) {
            int from = pair.first;
            const auto& edges = pair.second;
            
            for (const Edge& edge : edges) {
                sf::Vector2f startPos = nodePositions[from] + sf::Vector2f(20, 20);
                sf::Vector2f endPos = nodePositions[edge.to] + sf::Vector2f(20, 20);
                
                sf::Vertex line[] = {
                    sf::Vertex(startPos, sf::Color::White),
                    sf::Vertex(endPos, sf::Color::White)
                };

                if (isInPath(from, edge.to, path)) {
                    sf::Color pathColor = finalPath ? sf::Color::Green : sf::Color::Yellow;
                    line[0].color = pathColor;
                    line[1].color = pathColor;
                }
                
                window.draw(line, 2, sf::Lines);

                // Draw weight
                sf::Text weightText;
                weightText.setFont(font);
                weightText.setString(std::to_string(edge.weight));
                weightText.setCharacterSize(15);
                weightText.setFillColor(sf::Color::White);
                weightText.setPosition((startPos + endPos) / 2.0f);
                window.draw(weightText);
            }
        }

        // Draw nodes
        for (const auto& pair : nodes) {
            int id = pair.first;
            auto node = pair.second;
            
            if (finalPath && std::find(path.begin(), path.end(), id) != path.end()) {
                node.setFillColor(sf::Color::Green);
            }
            
            window.draw(node);
            
            sf::Text idText;
            idText.setFont(font);
            idText.setString(std::to_string(id));
            idText.setCharacterSize(20);
            idText.setFillColor(sf::Color::Black);
            idText.setPosition(nodePositions[id] + sf::Vector2f(15, 10));
            window.draw(idText);
        }

        // Draw status
        sf::Text statusText;
        statusText.setFont(font);
        statusText.setString(currentStatus);
        statusText.setCharacterSize(16);
        statusText.setFillColor(sf::Color::White);
        statusText.setPosition(10, 570);
        window.draw(statusText);

        // Draw distances
        std::stringstream distanceStr;
        distanceStr << "Current distances from start: ";
        for (const auto& pair : distances) {
            if (pair.second == std::numeric_limits<int>::max())
                distanceStr << pair.first << ": INF, ";
            else
                distanceStr << pair.first << ": " << pair.second << ", ";
        }
        
        sf::Text distanceText;
        distanceText.setFont(font);
        distanceText.setString(distanceStr.str());
        distanceText.setCharacterSize(16);
        distanceText.setFillColor(sf::Color::Yellow);
        distanceText.setPosition(10, 550);
        window.draw(distanceText);
    }

    std::vector<int> dijkstra(int start, int end, sf::RenderWindow& window) {
        std::map<int, int> dist;
        std::map<int, int> prev;
        std::priority_queue<std::pair<int, int>, 
                          std::vector<std::pair<int, int>>, 
                          std::greater<>> pq;

        currentStatus = "Initializing distances to infinity...";
        for (const auto& pair : nodes) {
            int id = pair.first;
            dist[id] = std::numeric_limits<int>::max();
            prev[id] = -1;
        }
        
        dist[start] = 0;
        distances = dist;
        currentStatus = "Setting distance to start node " + std::to_string(start) + " as 0";
        updateVisualization(window, {});
        
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (currentDist > dist[u]) {
                currentStatus = "Skipping node " + std::to_string(u) + " as we found a better path already";
                continue;
            }

            nodes[u].setFillColor(sf::Color::Cyan);
            
            currentStatus = "Processing node " + std::to_string(u) + " (current distance: " + std::to_string(currentDist) + ")";
            std::vector<int> currentPath = reconstructPath(prev, start, u);
            updateVisualization(window, currentPath);

            if (u == end) {
                currentStatus = "Found shortest path to target node " + std::to_string(end) + "!";
                updateVisualization(window, currentPath, true);
                std::this_thread::sleep_for(std::chrono::seconds(5));
                nodes[u].setFillColor(sf::Color::White);
                return currentPath;
            }

            for (const Edge& edge : adjList[u]) {
                int v = edge.to;
                int weight = edge.weight;
                
                currentStatus = "Checking edge " + std::to_string(u) + " -> " + 
                              std::to_string(v) + " (weight: " + std::to_string(weight) + ")";
                updateVisualization(window, currentPath);
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    distances = dist;
                    
                    currentStatus = "Found better path to " + std::to_string(v) + 
                                  " through " + std::to_string(u) + 
                                  " (new distance: " + std::to_string(dist[v]) + ")";
                    pq.push({dist[v], v});
                    updateVisualization(window, currentPath);
                }
            }

            nodes[u].setFillColor(sf::Color::White);
        }

        return reconstructPath(prev, start, end);
    }
};

class Maze {
public:
    Maze(int width, int height, int cellSize);
    void generateMaze();
    bool solveMaze(sf::RenderWindow& window);
    bool solveMazeBFS(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    enum Cell { WALL, PATH, VISITED, START, END, SOLUTION };

    struct Position {
        int x, y;
        Position(int x, int y) : x(x), y(y) {}
    };

    int width, height, cellSize;
    std::vector<std::vector<Cell>> grid;
    Position start, end;

    void generateDFS(Position pos);
    bool solveDFS(Position pos, sf::RenderWindow& window);
    std::vector<Position> getNeighbors(const Position& pos);
};

// Implementation of Maze class
Maze::Maze(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize), start(1, 1), end(width - 2, height - 2) {
    grid.resize(width, std::vector<Cell>(height, WALL));
    generateMaze();
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void Maze::generateMaze() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            grid[x][y] = WALL;
        }
    }
    generateDFS(start);
    grid[start.x][start.y] = START;
    grid[end.x][end.y] = END;
}

void Maze::generateDFS(Position pos) {
    grid[pos.x][pos.y] = PATH;
    std::vector<Position> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

    for (const Position& direction : directions) {
        int nx = pos.x + direction.x;
        int ny = pos.y + direction.y;

        if (nx > 0 && ny > 0 && nx < width - 1 && ny < height - 1 && grid[nx][ny] == WALL) {
            grid[nx][ny] = PATH;
            grid[pos.x + direction.x / 2][pos.y + direction.y / 2] = PATH;
            generateDFS({nx, ny});
        }
    }
}

bool Maze::solveMaze(sf::RenderWindow& window) {
    return solveDFS(start, window);
}

bool Maze::solveMazeBFS(sf::RenderWindow& window) {
    std::queue<Position> q;
    q.push(start);
    grid[start.x][start.y] = VISITED;

    while (!q.empty()) {
        Position pos = q.front();
        q.pop();

        if (pos.x == end.x && pos.y == end.y) {
            grid[pos.x][pos.y] = SOLUTION;
            return true;
        }

        draw(window);
        window.display();
        sf::sleep(sf::milliseconds(200));

        std::vector<Position> neighbors = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (const Position& dir : neighbors) {
            int nx = pos.x + dir.x;
            int ny = pos.y + dir.y;

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && (grid[nx][ny] == PATH || grid[nx][ny] == END)) {
                q.push({nx, ny});
                grid[nx][ny] = VISITED;
            }
        }
    }
    return false;
}

bool Maze::solveDFS(Position pos, sf::RenderWindow& window) {
    if (pos.x == end.x && pos.y == end.y) {
        grid[pos.x][pos.y] = SOLUTION;
        return true;
    }

    grid[pos.x][pos.y] = VISITED;
    draw(window);
    window.display();
    sf::sleep(sf::milliseconds(200));

    std::vector<Position> neighbors = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    for (const Position& dir : neighbors) {
        int nx = pos.x + dir.x;
        int ny = pos.y + dir.y;

        if (grid[nx][ny] == PATH || grid[nx][ny] == END) {
            if (solveDFS({nx, ny}, window)) {
                grid[pos.x][pos.y] = SOLUTION;
                draw(window);
                window.display();
                sf::sleep(sf::milliseconds(50));
                return true;
            }
        }
    }

    grid[pos.x][pos.y] = PATH;
    return false;
}

void Maze::draw(sf::RenderWindow& window) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(x * cellSize, y * cellSize);

            switch (grid[x][y]) {
                case WALL: cell.setFillColor(sf::Color::Black); break;
                case PATH: cell.setFillColor(sf::Color::White); break;
                case VISITED: cell.setFillColor(sf::Color::Blue); break;
                case START: cell.setFillColor(sf::Color::Green); break;
                case END: cell.setFillColor(sf::Color::Red); break;
                case SOLUTION: cell.setFillColor(sf::Color::Yellow); break;
            }

            window.draw(cell);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Integrated Data Structure Visualizer");
    sf::Font font;

    if (!font.loadFromFile("DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    std::vector<int> array;
    LinkedList linkedList;
    Stack stack;
    Queue queue;
    AVLTree avlTree;
    Graph graph;
    Maze maze(21, 21, 20);

    sf::Text titleText("Main Menu", font, 30);
    titleText.setPosition(300, 20);

    sf::Text menuText("", font, 20);
    menuText.setPosition(50, 80);
    menuText.setString(
        "1. Searching\n2. Sorting\n3. Linked List-Lineal(DS)\n4. Stack-Lineal(DS)\n"
        "5. Queue-Lineal(DS)\n6. AVL Tree-NoLineal(DS)\n7. Graph Visualization\n8. Maze Solver\nPress Esc to Exit");


    sf::Text outputText("", font, 20);
    outputText.setPosition(50, 250);

    bool searchMode = false, sortMode = false, linkedListMode = false;
    bool stackMode = false, queueMode = false, avlMode = false, graphMode = false, mazeMode = false;
    bool showAvlText = true;  
    std::string avlInput = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }

               if (!searchMode && !sortMode && !linkedListMode &&
    !stackMode && !queueMode && !avlMode && !graphMode && !mazeMode) {
    if (event.key.code == sf::Keyboard::Num1) {
        searchMode = true;
        menuText.setString(
            "Searching Menu:\n"
            "L - Linear Search (O(n))\n"
            "B - Binary Search (O(log n))\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num2) {
        sortMode = true;
        menuText.setString(
            "Sorting Menu:\n"
            "B - Bubble Sort (O(n^2))\n"
            "I - Insertion Sort (O(n^2))\n"
            "S - Selection Sort (O(n^2))\n"
            "Q - Quick Sort (O(n log n))\n"
            "M - Merge Sort (O(n log n))\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num3) {
        linkedListMode = true;
        menuText.setString(
            "Linked List Menu:\n"
            "A - Insert (O(1) at head)\n"
            "R - Remove (O(1) at head)\n"
            "V - Reverse (O(n))\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num4) {
        stackMode = true;
        menuText.setString(
            "Stack Menu:\n"
            "A - Push (O(1))\n"
            "R - Pop (O(1))\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num5) {
        queueMode = true;
        menuText.setString(
            "Queue Menu:\n"
            "A - Enqueue (O(1))\n"
            "R - Dequeue (O(1))\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num6) {
        avlMode = true;
        showAvlText = true;
        menuText.setString(
            "AVL Tree Menu:\n"
            "Insert (O(log n))\n"
            "Backspace - Delete\n"
            "Enter - Insert\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num7) {
        graphMode = true;
        menuText.setString(
            "Graph Visualization:\n"
            "Press 1-8 for Dijkstra (O(V + E))\n"
            "0 - Back"
        );
    } else if (event.key.code == sf::Keyboard::Num8) {
        mazeMode = true;
        menuText.setString(
            "Maze Solver:\n"
            "S - Solve BFS (O(V + E))\n"
            "D - Solve DFS (O(V + E))\n"
            "0 - Back"
        );
    }
}
                if (searchMode) {
                    if (event.key.code == sf::Keyboard::L) {
                        inputArrayInWindow(array, outputText, font, window);
                        performLinearSearch(array, outputText, font, window);
                    } else if (event.key.code == sf::Keyboard::B) {
                        inputArrayInWindow(array, outputText, font, window);
                        performBinarySearch(array, outputText, font, window);
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        searchMode = false;
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    }
                }

                if (sortMode) {
                    if (event.key.code == sf::Keyboard::B) {
                        inputArrayInWindow(array, outputText, font, window);
                        performSorting(array, outputText, "Bubble");
                    } else if (event.key.code == sf::Keyboard::I) {
                        inputArrayInWindow(array, outputText, font, window);
                        performSorting(array, outputText, "Insertion");
                    } else if (event.key.code == sf::Keyboard::S) {
                        inputArrayInWindow(array, outputText, font, window);
                        performSorting(array, outputText, "Selection");
                    } else if (event.key.code == sf::Keyboard::Q) {
                        inputArrayInWindow(array, outputText, font, window);
                        performSorting(array, outputText, "Quick");
                    } else if (event.key.code == sf::Keyboard::M) {
                        inputArrayInWindow(array, outputText, font, window);
                        performSorting(array, outputText, "Merge");
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        sortMode = false;
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    }
                }

                if (linkedListMode) {
                    if (event.key.code == sf::Keyboard::A) {
                        linkedList.insert(rand() % 100);
                        updateOutput("Inserted a random value into the Linked List.", outputText);
                    } else if (event.key.code == sf::Keyboard::R) {
                        linkedList.remove();
                        updateOutput("Removed a value from the Linked List.", outputText);
                    } else if (event.key.code == sf::Keyboard::V) {
                        linkedList.reverse();
                        updateOutput("Reversed the Linked List.", outputText);
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        linkedListMode = false;
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    }
                }

                if (stackMode) {
                    if (event.key.code == sf::Keyboard::A) {
                        stack.push(rand() % 100);
                        updateOutput("Pushed a random value onto the Stack.", outputText);
                    } else if (event.key.code == sf::Keyboard::R) {
                        stack.pop();
                        updateOutput("Popped a value from the Stack.", outputText);
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        stackMode = false;
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    }
                }

                if (queueMode) {
                    if (event.key.code == sf::Keyboard::A) {
                        queue.enqueue(rand() % 100);
                        updateOutput("Enqueued a random value into the Queue.", outputText);
                    } else if (event.key.code == sf::Keyboard::R) {
                        queue.dequeue();
                        updateOutput("Dequeued a value from the Queue.", outputText);
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        queueMode = false;
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    }
                }

                if (avlMode) {
                    if (event.key.code == sf::Keyboard::Enter && !avlInput.empty()) {
                        try {
                            int value = std::stoi(avlInput);
                            avlTree.insert(value, window, font);
                            showAvlText = false;  // Hide text after successful insertion
                            avlInput.clear();
                        } catch (const std::invalid_argument&) {
                            updateOutput("Invalid input. Please enter a valid number.", outputText);
                            avlInput.clear();
                        }
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        avlMode = false;
                        showAvlText = true;  // Reset text visibility when exiting AVL mode
                        avlInput.clear();
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    } else {
                        showAvlText = true;  // Show text when any other key is pressed
                    }
                }

                if (graphMode) {
                    if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num8) {
                        int startNode = event.key.code - sf::Keyboard::Num1 + 1;
                        graph.dijkstra(startNode, 8, window);
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        graphMode = false;
                        menuText.setString("1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n5. Queue\n6. AVL Tree\n7. Graph Visualization\nPress Esc to Exit");
                    }
                }

                // Maze solver mode
                if (mazeMode) {
                    if (event.key.code == sf::Keyboard::S) {
                        maze.solveMazeBFS(window); // Solve maze and display progress
                    } else if (event.key.code == sf::Keyboard::Num0) {
                        mazeMode = false;
                        menuText.setString(
                            "1. Searching\n2. Sorting\n3. Linked List\n4. Stack\n"
                            "5. Queue\n6. AVL Tree\n7. Graph Visualization\n8. Maze Solver\nPress Esc to Exit");
                    }
                }
            }

            if (avlMode && event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    avlInput += static_cast<char>(event.text.unicode);
                    showAvlText = true;  // Show text when typing
                } else if (event.text.unicode == 8 && !avlInput.empty()) {
                    avlInput.pop_back();
                    showAvlText = true;  // Show text when deleting
                }
            }
        }

        window.clear(sf::Color::Black);

        if (!avlMode || showAvlText) {
            window.draw(titleText);
            window.draw(menuText);
            window.draw(outputText);
        }

        if (linkedListMode) {
            linkedList.draw(window, font);
        } else if (stackMode) {
            stack.draw(window, font);
        } else if (queueMode) {
            queue.draw(window, font);
        } else if (avlMode) {
            avlTree.draw(window, font);
            if (showAvlText) {  // Only draw input text if text should be shown
                sf::Text avlInputText("Input: " + avlInput, font, 20);
                avlInputText.setFillColor(sf::Color::White);
                avlInputText.setPosition(10, 550);
                window.draw(avlInputText);
            }
        } else if (graphMode) {
            graph.draw(window);
        }

        window.display();
    }

    return 0;
}