/* Author Ricardo Fabbri rfabbri@iprj.uerj.br 2025 */
#include <iostream>
#include "tree.h"

int main() {
    struct Node* root = NULL;
    int key;

    while (std::cin >> key) {
        root = insert(root, key);
    }

    inorder(root);
    std::cout << std::endl;

    return 0;
}
