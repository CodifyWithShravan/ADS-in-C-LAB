#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to find LCA in a BST
Node* findLCA_BST(Node* root, int n1, int n2) {
    // Loop until we find the LCA
    while (root != NULL) {
        // If both nodes are smaller, move left
        if (n1 < root->data && n2 < root->data) {
            root = root->left;
        }
        // If both nodes are larger, move right
        else if (n1 > root->data && n2 > root->data) {
            root = root->right;
        }
        // Otherwise, we've found the split point (LCA)
        else {
            break;
        }
    }
    return root;
}

int main() {
    Node* root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);

    int n1 = 10, n2 = 14;
    Node* lca = findLCA_BST(root, n1, n2);

    if (lca != NULL) {
        printf("LCA of %d and %d is %d\n", n1, n2, lca->data);
    } else {
        printf("LCA not found for %d and %d\n", n1, n2);
    }

    return 0;
}