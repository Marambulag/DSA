#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}  // Constructor de nodo
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void addNode(int value);                 
    void insertAtHead(int value);            
    void insertAtPosition(int value, int position);  
    void deleteNode(int value);              
    bool search(int value) const;            
    void showList() const;                  

private:
    Node* head;
};

#endif
