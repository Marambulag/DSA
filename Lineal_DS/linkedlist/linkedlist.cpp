#include "linkedlist.hpp"
#include <iostream>

using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

void LinkedList::addNode(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::insertAtHead(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void LinkedList::insertAtPosition(int value, int position) {
    if (position == 0) {
        insertAtHead(value);
        return;
    }

    Node* newNode = new Node(value);
    Node* temp = head;
    for (int i = 1; i < position; ++i) {
        if (temp == nullptr) {
            cout << "Position out of range" << endl;
            delete newNode;
            return;
        }
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void LinkedList::deleteNode(int value) {
    if (head == nullptr) return;

    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Value not found" << endl;
        return;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
}

bool LinkedList::search(int value) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == value) return true;
        temp = temp->next;
    }
    return false;
}

void LinkedList::showList() const {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}