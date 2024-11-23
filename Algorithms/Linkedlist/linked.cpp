#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void addNode(Node* &head, int value){
    Node* newNode = new Node(); // create a new node in memory
    newNode->data = value; // Assign the value to the new node's data field
    newNode->next = nullptr; // The next node is initially null

    if(head == nullptr){
        head = newNode; // If the list is empty, the new node becomes the head
    } else {
        Node* temp = head; // Create a temp variable to traverse the list
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode; // Link the last node to the new node
    }
}

void showList(Node* head){
    Node* temp = head;
    while(temp != nullptr){
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl; // Indicate the end of the list
}

int main()
{
    Node* list = nullptr; // Initialize the list as empty (nullptr)

    addNode(list, 40); // Add values to the list
    addNode(list, 10);
    addNode(list, 890);

    showList(list); // Display the list

    return 0;
}
