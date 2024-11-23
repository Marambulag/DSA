#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void addNode(Node* &head, int value){
    Node* newNode new.Node(); //crear un nuevo nodo en memoria
    newNode -> data = value; // Asignacion de value a la estructura accediendo a data
    newNode -> next = nullptr; // el siguiente nodo es null ptr

    if(head = nullptr){
        head = newnode; // si la lista esta vacia el nuevo nodo es la head
    {else}
        Node* temp = head; // crear una variable temporal que almecene el current head
        while(temp -> next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void showlist(Node* head){
    Node* temp = head;
    while(temp != nullptr){
        cout << temp -> data << "->";
        temp = temp -> next;
    }
}


int main()
{
    Node* list = nullptr;
    addNote([&]list, value 40);
    addNote([&]list, value 10);
    addNote([&]list, value 890);

    return 0;
}