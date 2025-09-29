#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "Utils.hpp"
#include "Algorithms.hpp"
#include "InputHelpers.hpp"
#include "Operations.hpp"
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "QueueDS.hpp"
#include "AVLTree.hpp"
#include "Graph.hpp"
#include "Maze.hpp"
#include "Menu.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Integrated Data Structure Visualizer", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    std::vector<int> array;
    LinkedList linkedList;
    Stack stack;
    QueueDS queue;
    AVLTree avlTree;
    Graph graph;
    Maze maze(21, 21, 20);

    // Animated gradient-ish background using two rectangles cross-fading
    sf::RectangleShape bg1({800.f, 600.f});
    bg1.setFillColor(sf::Color(30, 32, 36));
    sf::RectangleShape bg2({800.f, 600.f});
    bg2.setFillColor(sf::Color(40, 44, 48));
    float bgAlpha = 0.f;

    // Replace static main menu with interactive Menu component
    std::vector<std::string> mainItems = {
        "Searching",
        "Sorting",
        "Linked List (Linear DS)",
        "Stack (Linear DS)",
        "Queue (Linear DS)",
        "AVL Tree (Non-Linear DS)",
        "Graph Visualization",
        "Maze Solver",
        "Exit"
    };
    Menu mainMenu(font, mainItems, {40.f, 80.f}, 380.f);

    // New: interactive submenus
    Menu searchMenu(font, {"Linear Search", "Binary Search", "Back"}, {40.f, 140.f}, 360.f);
    Menu sortMenu(font, {"Bubble", "Insertion", "Selection", "Quick", "Merge", "Back"}, {40.f, 140.f}, 360.f);

    sf::Text outputText("", font, 20);
    outputText.setPosition(50, 520);

    bool searchMode = false, sortMode = false, linkedListMode = false;
    bool stackMode = false, queueMode = false, avlMode = false, graphMode = false, mazeMode = false;
    bool showAvlText = true;  
    std::string avlInput = "";

    // New: typed input buffers for DS modes
    std::string listInput, stackInput, queueInput;
    bool showListInput = true, showStackInput = true, showQueueInput = true;

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (searchMode || sortMode || linkedListMode || stackMode || queueMode || avlMode || graphMode || mazeMode) {
                    searchMode = sortMode = linkedListMode = stackMode = queueMode = avlMode = graphMode = mazeMode = false;
                    listInput.clear(); stackInput.clear(); queueInput.clear();
                } else {
                    window.close();
                }
            }

            // Menu interactions only when in root menu
            if (!searchMode && !sortMode && !linkedListMode &&
                !stackMode && !queueMode && !avlMode && !graphMode && !mazeMode) {
                // Existing menu (keyboard/mouse) interaction
                if (mainMenu.handleEvent(event, window)) {
                    switch (mainMenu.getSelectedIndex()) {
                        case 0: searchMode = true; break;
                        case 1: sortMode = true; break;
                        case 2: linkedListMode = true; break;
                        case 3: stackMode = true; break;
                        case 4: queueMode = true; break;
                        case 5: avlMode = true; showAvlText = true; avlInput.clear(); break;
                        case 6: graphMode = true; break;
                        case 7: mazeMode = true; break;
                        case 8: window.close(); break;
                    }
                }
                // New: quick hotkeys 1-9 mirror the menu selection
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                        int idx = event.key.code - sf::Keyboard::Num1; // 0-based
                        if (idx == 0) searchMode = true;
                        else if (idx == 1) sortMode = true;
                        else if (idx == 2) linkedListMode = true;
                        else if (idx == 3) stackMode = true;
                        else if (idx == 4) queueMode = true;
                        else if (idx == 5) { avlMode = true; showAvlText = true; avlInput.clear(); }
                        else if (idx == 6) graphMode = true;
                        else if (idx == 7) mazeMode = true;
                        else if (idx == 8) window.close();
                    }
                    // Root-level letter fallbacks similar to older behavior
                    else if (event.key.code == sf::Keyboard::L) { searchMode = true; }
                    else if (event.key.code == sf::Keyboard::S) { sortMode = true; }
                    else if (event.key.code == sf::Keyboard::A) { avlMode = true; showAvlText = true; avlInput.clear(); }
                    else if (event.key.code == sf::Keyboard::G) { graphMode = true; }
                    else if (event.key.code == sf::Keyboard::M) { mazeMode = true; }
                    else if (event.key.code == sf::Keyboard::Q) { queueMode = true; }
                    else if (event.key.code == sf::Keyboard::K) { stackMode = true; }
                    else if (event.key.code == sf::Keyboard::N) { linkedListMode = true; }
                }
            }

            // New: interactive Search submenu
            if (searchMode) {
                if (searchMenu.handleEvent(event, window)) {
                    int sel = searchMenu.getSelectedIndex();
                    if (sel == 0) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performLinearSearch(array, outputText, font, window);
                    } else if (sel == 1) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performBinarySearch(array, outputText, font, window);
                    } else if (sel == 2) {
                        searchMode = false;
                    }
                }
                // Fallback legacy hotkeys and number shortcuts
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::L || event.key.code == sf::Keyboard::Num1) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performLinearSearch(array, outputText, font, window);
                    } else if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::Num2) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performBinarySearch(array, outputText, font, window);
                    } else if (event.key.code == sf::Keyboard::Num3) {
                        searchMode = false;
                    }
                }
            }

            // New: interactive Sort submenu
            if (sortMode) {
                if (sortMenu.handleEvent(event, window)) {
                    int sel = sortMenu.getSelectedIndex();
                    if (sel >= 0 && sel <= 4) {
                        static const char* names[] = {"Bubble", "Insertion", "Selection", "Quick", "Merge"};
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performSorting(array, outputText, names[sel], window, font);
                    } else if (sel == 5) {
                        sortMode = false;
                    }
                }
                // Fallback legacy hotkeys and number shortcuts
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::Num1) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performSorting(array, outputText, "Bubble", window, font);
                    } else if (event.key.code == sf::Keyboard::I || event.key.code == sf::Keyboard::Num2) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performSorting(array, outputText, "Insertion", window, font);
                    } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Num3) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performSorting(array, outputText, "Selection", window, font);
                    } else if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Num4) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performSorting(array, outputText, "Quick", window, font);
                    } else if (event.key.code == sf::Keyboard::M || event.key.code == sf::Keyboard::Num5) {
                        input_helpers::inputArrayInWindow(array, outputText, font, window);
                        operations::performSorting(array, outputText, "Merge", window, font);
                    } else if (event.key.code == sf::Keyboard::Num6) {
                        sortMode = false;
                    }
                }
            }

            // Existing modes
            if (linkedListMode) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        listInput += static_cast<char>(event.text.unicode);
                        showListInput = true;
                    } else if (event.text.unicode == 8 && !listInput.empty()) { // backspace
                        listInput.pop_back();
                        showListInput = true;
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !listInput.empty()) {
                        int value = std::stoi(listInput);
                        linkedList.insert(value);
                        utils::updateOutput("Inserted " + std::to_string(value) + " into the Linked List.", outputText);
                        listInput.clear();
                        showListInput = true;
                    } else if (event.key.code == sf::Keyboard::A) {
                        linkedList.insert(rand() % 100);
                        utils::updateOutput("Inserted a random value into the Linked List.", outputText);
                    } else if (event.key.code == sf::Keyboard::R) {
                        linkedList.remove();
                        utils::updateOutput("Removed a value from the Linked List.", outputText);
                    } else if (event.key.code == sf::Keyboard::V) {
                        linkedList.reverse();
                        utils::updateOutput("Reversed the Linked List.", outputText);
                    }
                }
            }

            if (stackMode) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        stackInput += static_cast<char>(event.text.unicode);
                        showStackInput = true;
                    } else if (event.text.unicode == 8 && !stackInput.empty()) {
                        stackInput.pop_back();
                        showStackInput = true;
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !stackInput.empty()) {
                        int value = std::stoi(stackInput);
                        stack.push(value);
                        utils::updateOutput("Pushed " + std::to_string(value) + " onto the Stack.", outputText);
                        stackInput.clear();
                        showStackInput = true;
                    } else if (event.key.code == sf::Keyboard::A) {
                        stack.push(rand() % 100);
                        utils::updateOutput("Pushed a random value onto the Stack.", outputText);
                    } else if (event.key.code == sf::Keyboard::R) {
                        stack.pop();
                        utils::updateOutput("Popped a value from the Stack.", outputText);
                    }
                }
            }

            if (queueMode) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        queueInput += static_cast<char>(event.text.unicode);
                        showQueueInput = true;
                    } else if (event.text.unicode == 8 && !queueInput.empty()) {
                        queueInput.pop_back();
                        showQueueInput = true;
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !queueInput.empty()) {
                        int value = std::stoi(queueInput);
                        queue.enqueue(value);
                        utils::updateOutput("Enqueued " + std::to_string(value) + " into the Queue.", outputText);
                        queueInput.clear();
                        showQueueInput = true;
                    } else if (event.key.code == sf::Keyboard::A) {
                        queue.enqueue(rand() % 100);
                        utils::updateOutput("Enqueued a random value into the Queue.", outputText);
                    } else if (event.key.code == sf::Keyboard::R) {
                        queue.dequeue();
                        utils::updateOutput("Dequeued a value from the Queue.", outputText);
                    }
                }
            }

            if (avlMode) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        avlInput += static_cast<char>(event.text.unicode);
                        showAvlText = true;
                    } else if (event.text.unicode == 8 && !avlInput.empty()) {
                        avlInput.pop_back();
                        showAvlText = true;
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !avlInput.empty()) {
                        try {
                            int value = std::stoi(avlInput);
                            avlTree.insert(value, window, font);
                            showAvlText = false;
                            avlInput.clear();
                        } catch (const std::invalid_argument&) {
                            utils::updateOutput("Invalid input. Please enter a valid number.", outputText);
                            avlInput.clear();
                        }
                    }
                }
            }

            if (graphMode && event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num8) {
                    int startNode = event.key.code - sf::Keyboard::Num1 + 1;
                    graph.dijkstra(startNode, 8, window);
                }
            }

            if (mazeMode && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    maze.resetTraversal();
                    bool ok = maze.solveMazeBFS(window);
                    // Keep view until ESC; don't auto-leave maze mode
                } else if (event.key.code == sf::Keyboard::D) {
                    maze.resetTraversal();
                    bool ok = maze.solveMazeDFS(window);
                    // Keep view until ESC; don't auto-leave maze mode
                }
            }
        }

        // Soft animated background cross-fade
        bgAlpha += dt * 0.25f; // slow pulse
        float mix = (std::sin(bgAlpha) + 1.f) * 0.5f; // 0..1
        sf::Color c1 = bg1.getFillColor();
        sf::Color c2 = bg2.getFillColor();
        sf::Color blended(
            static_cast<sf::Uint8>(c1.r * (1 - mix) + c2.r * mix),
            static_cast<sf::Uint8>(c1.g * (1 - mix) + c2.g * mix),
            static_cast<sf::Uint8>(c1.b * (1 - mix) + c2.b * mix)
        );
        bg1.setFillColor(blended);

        // Update menu animations
        mainMenu.update(dt);
        searchMenu.update(dt);
        sortMenu.update(dt);

        window.clear();
        window.draw(bg1);

        // Root menu vs modes
        if (!searchMode && !sortMode && !linkedListMode && !stackMode && !queueMode && !avlMode && !graphMode && !mazeMode) {
            mainMenu.draw(window);
            // Helper hint text
            sf::Text hint("Use Up/Down + Enter, 1-9 or L/S/N/K/Q/A/G/M. ESC to exit.", font, 16);
            hint.setFillColor(sf::Color(200, 200, 210));
            hint.setPosition(40.f, 480.f);
            window.draw(hint);
        } else {
            // Mode content
            if (searchMode) {
                sf::Text title("Searching", font, 22);
                title.setFillColor(sf::Color(220, 220, 230));
                title.setPosition(40.f, 90.f);
                window.draw(title);
                searchMenu.draw(window);
            } else if (sortMode) {
                sf::Text title("Sorting", font, 22);
                title.setFillColor(sf::Color(220, 220, 230));
                title.setPosition(40.f, 90.f);
                window.draw(title);
                sortMenu.draw(window);
            } else if (linkedListMode) {
                linkedList.draw(window, font);
                // Input hint and buffer display
                sf::Text hint("Linked List: type number + Enter to insert | A random | R remove | V reverse", font, 16);
                hint.setFillColor(sf::Color(200, 200, 210));
                hint.setPosition(40.f, 40.f);
                window.draw(hint);
                if (showListInput) {
                    sf::Text in("Value: " + listInput, font, 18);
                    in.setFillColor(sf::Color(220, 240, 255));
                    in.setPosition(40.f, 70.f);
                    window.draw(in);
                }
            } else if (stackMode) {
                stack.draw(window, font);
                sf::Text hint("Stack: type number + Enter to push | A random | R pop", font, 16);
                hint.setFillColor(sf::Color(200, 200, 210));
                hint.setPosition(40.f, 40.f);
                window.draw(hint);
                if (showStackInput) {
                    sf::Text in("Value: " + stackInput, font, 18);
                    in.setFillColor(sf::Color(220, 240, 255));
                    in.setPosition(40.f, 70.f);
                    window.draw(in);
                }
            } else if (queueMode) {
                queue.draw(window, font);
                sf::Text hint("Queue: type number + Enter to enqueue | A random | R dequeue", font, 16);
                hint.setFillColor(sf::Color(200, 200, 210));
                hint.setPosition(40.f, 40.f);
                window.draw(hint);
                if (showQueueInput) {
                    sf::Text in("Value: " + queueInput, font, 18);
                    in.setFillColor(sf::Color(220, 240, 255));
                    in.setPosition(40.f, 70.f);
                    window.draw(in);
                }
            } else if (avlMode) {
                avlTree.draw(window, font);
                if (showAvlText) {
                    sf::Text avlInputText("AVL Insert Value: " + avlInput, font, 20);
                    avlInputText.setFillColor(sf::Color::White);
                    avlInputText.setPosition(10, 550);
                    window.draw(avlInputText);
                }
            } else if (graphMode) {
                graph.draw(window);
            } else if (mazeMode) {
                maze.draw(window);
                sf::Text hint("Maze: S = Solve BFS, D = Solve DFS", font, 16);
                hint.setFillColor(sf::Color(200, 200, 210));
                float hintX = static_cast<float>(window.getSize().x) - 300.f; // move to the right
                hint.setPosition(hintX, 40.f);
                window.draw(hint);
            }

            window.draw(outputText);

            // Back hint and per-mode help
            sf::Text backHint("Press ESC to go back to menu", font, 16);
            backHint.setFillColor(sf::Color(200, 200, 210));
            backHint.setPosition(40.f, 480.f);
            window.draw(backHint);
        }

        window.display();
    }

    return 0;
}