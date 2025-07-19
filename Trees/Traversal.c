#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Structure for a binary tree node.
 * * Each node contains an integer data payload, and pointers to its
 * left and right children.
 */
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

/**
 * @brief Helper function to allocate a new node with the given data.
 * * @param data The integer value for the new node.
 * @return A pointer to the newly created node.
 */
struct Node* createNode(int data) {
    // Allocate memory for the new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Check if memory allocation was successful
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1); // Exit if memory cannot be allocated
    }
    
    // Assign data and initialize children to NULL
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

/**
 * @brief Inserts a new node into the Binary Search Tree (BST).
 * * This function recursively finds the correct position for the new data
 * based on BST rules (smaller values go left, larger or equal values go right).
 * * @param node The root of the current subtree.
 * @param data The integer value to insert.
 * @return The root of the modified subtree.
 */
struct Node* insertNode(struct Node* node, int data) {
    // If the tree or subtree is empty, create a new node and return it
    if (node == NULL) {
        return createNode(data);
    }
    
    // Recur down the tree to find the correct spot
    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else { // data >= node->data
        node->right = insertNode(node->right, data);
    }
    
    // Return the (unchanged) node pointer
    return node;
}


/**
 * @brief Performs and prints an Inorder traversal of the tree.
 * Traversal Order: Left Subtree -> Root -> Right Subtree
 * * @param node The root of the current subtree.
 */
void printInorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%d ", node->data);
    printInorder(node->right);
}

/**
 * @brief Performs and prints a Preorder traversal of the tree.
 * Traversal Order: Root -> Left Subtree -> Right Subtree
 * * @param node The root of the current subtree.
 */
void printPreorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

/**
 * @brief Performs and prints a Postorder traversal of the tree.
 * Traversal Order: Left Subtree -> Right Subtree -> Root
 * * @param node The root of the current subtree.
 */
void printPostorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->data);
}

/**
 * @brief Main function with a menu-driven interface.
 * * Allows the user to insert nodes and choose a traversal method to print,
 * or exit the program.
 */
int main() {
    struct Node* root = NULL; // Initially, the tree is empty
    int choice, data;

    // Main loop to display the menu and handle user input
    while (1) {
        printf("\n--- Binary Tree Menu ---\n");
        printf("1. Insert a node\n");
        printf("2. Print Inorder Traversal\n");
        printf("3. Print Preorder Traversal\n");
        printf("4. Print Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        // Read user's choice
        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer if the user enters non-integer input
            while (getchar() != '\n'); 
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                if (scanf("%d", &data) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid input. Please enter a number.\n");
                    continue;
                }
                root = insertNode(root, data);
                printf("Node with value %d inserted successfully.\n", data);
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty. Nothing to print.\n");
                } else {
                    printf("Inorder traversal: ");
                    printInorder(root);
                    printf("\n");
                }
                break;

            case 3:
                 if (root == NULL) {
                    printf("Tree is empty. Nothing to print.\n");
                } else {
                    printf("Preorder traversal: ");
                    printPreorder(root);
                    printf("\n");
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty. Nothing to print.\n");
                } else {
                    printf("Postorder traversal: ");
                    printPostorder(root);
                    printf("\n");
                }
                break;

            case 5:
                printf("Exiting program. Goodbye!\n");
                exit(0); // Terminate the program

            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}
