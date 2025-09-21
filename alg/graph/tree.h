/* Author Ricardo Fabbri rfabbri@iprj.uerj.br 2025 */
#ifndef TREE_H
#define TREE_H

struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new BST node
struct Node* newNode(int item);

// Function to insert a new node with given key in BST
struct Node* insert(struct Node* node, int key);

// Function to do inorder traversal of BST
void inorder(struct Node* root);

#endif /* TREE_H */
