#include <stdio.h>
#include <stdlib.h>

// Node structure for a binary tree
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into a BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to find the LCA in a BST
Node* findLCA_BST(Node* root, int n1, int n2) {
    if (root == NULL) {
        return NULL;
    }

    // Both nodes are in the left subtree
    if (n1 < root->data && n2 < root->data) {
        return findLCA_BST(root->left, n1, n2);
    }

    // Both nodes are in the right subtree
    if (n1 > root->data && n2 > root->data) {
        return findLCA_BST(root->right, n1, n2);
    }

    // One is on the left and one on the right, so the current node is the LCA
    return root;
}

int main() {
    Node* root = NULL;
    root = insert(root, 20);
    insert(root, 8);
    insert(root, 22);
    insert(root, 4);
    insert(root, 12);
    insert(root, 10);
    insert(root, 14);

    int n1 = 10, n2 = 14;
    Node* lca = findLCA_BST(root, n1, n2);

    if (lca != NULL) {
        printf("LCA of %d and %d is %d\n", n1, n2, lca->data);
    } else {
        printf("LCA not found for %d and %d\n", n1, n2);
    }

    return 0;
}