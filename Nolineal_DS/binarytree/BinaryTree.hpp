#ifndef BINARYTREE_H
#define BINARYTREE_H

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value);
};

class BinaryTree {
public:
    Node* root;

    BinaryTree();

    Node* insert(Node* node, int value);
    Node* search(Node* node, int value);
    Node* remove(Node* node, int value);
    Node* minValueNode(Node* node);

    void inOrderTraversal(Node* node);
    void preOrderTraversal(Node* node);
    void postOrderTraversal(Node* node);
};

#endif