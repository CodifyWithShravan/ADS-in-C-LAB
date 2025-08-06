#include <stdio.h>
#include <stdlib.h> // Required for malloc and free

// Definition of a BST node
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Function to create a new node
// Allocates memory for a new node and initializes its data and child pointers.
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1); // Exit if memory allocation fails
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the BST
// Recursively finds the correct position for the new node based on its data value.
struct node* insert(struct node* root, int data) {
    // If the tree is empty, create a new node and make it the root
    if (root == NULL) {
        return createNode(data);
    }

    // If data is less than root's data, go to the left subtree
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    // If data is greater than root's data, go to the right subtree
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // If data is equal, it's a duplicate (BSTs typically don't allow duplicates),
    // so we do nothing and return the current root.
    return root;
}

// Function to search for a value in the BST
// Recursively traverses the tree to find a node with the given data.
struct node* search(struct node* root, int data) {
    // Base cases: root is NULL (value not found) or data is found at root
    if (root == NULL || root->data == data) {
        return root;
    }

    // If data is smaller than root's data, search in the left subtree
    if (data < root->data) {
        return search(root->left, data);
    }
    // If data is greater than root's data, search in the right subtree
    return search(root->right, data);
}

// Function to find the node with the minimum value in a subtree
// Used in the deletion process for nodes with two children.
struct node* findMin(struct node* node) {
    struct node* current = node;
    // Loop down to find the leftmost leaf (smallest value)
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the BST
// Handles three cases: no child, one child, and two children.
struct node* deleteNode(struct node* root, int data) {
    // Base case: If the tree is empty, return NULL
    if (root == NULL) {
        return root;
    }

    // Traverse the tree to find the node to be deleted
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root); // Free the memory of the current node
            return temp; // Return the single child (or NULL if no child)
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root); // Free the memory of the current node
            return temp; // Return the single child
        }

        // Node with two children: Get the in-order successor (smallest in the right subtree)
        struct node* temp = findMin(root->right);

        // Copy the in-order successor's data to this node
        root->data = temp->data;

        // Delete the in-order successor from the right subtree
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function for in-order traversal of the BST
// Prints the elements in sorted order.
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);    // Traverse left subtree
        printf("%d ", root->data); // Print current node's data
        inorder(root->right);   // Traverse right subtree
    }
}

// Main function to demonstrate BST operations
int main() {
    struct node* root = NULL; // Initialize an empty BST

    // --- Insertion examples ---
    printf("Inserting elements: 50, 30, 20, 40, 70, 60, 80\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order traversal of the BST: ");
    inorder(root); // Should print: 20 30 40 50 60 70 80
    printf("\n\n");

    // --- Search examples ---
    int searchValue1 = 40;
    struct node* result1 = search(root, searchValue1);
    if (result1 != NULL) {
        printf("Found %d in the BST.\n", searchValue1);
    } else {
        printf("Did not find %d in the BST.\n", searchValue1);
    }

    int searchValue2 = 90;
    struct node* result2 = search(root, searchValue2);
    if (result2 != NULL) {
        printf("Found %d in the BST.\n", searchValue2);
    } else {
        printf("Did not find %d in the BST.\n", searchValue2);
    }
    printf("\n");

    // --- Deletion examples ---

    // Case 1: Delete a node with two children (e.g., 50 - the root)
    printf("Deleting node 50 (root with two children).\n");
    root = deleteNode(root, 50);
    printf("In-order traversal after deleting 50: ");
    inorder(root); // Expected: 20 30 40 60 70 80 (50 replaced by 60, then 60 deleted from right subtree)
    printf("\n\n");

    // Case 2: Delete a leaf node (e.g., 20)
    printf("Deleting node 20 (leaf node).\n");
    root = deleteNode(root, 20);
    printf("In-order traversal after deleting 20: ");
    inorder(root); // Expected: 30 40 60 70 80
    printf("\n\n");

    // Case 3: Delete a node with one child (e.g., 70, assuming 80 is its only child after 50 is deleted)
    printf("Deleting node 70 (node with one child).\n");
    root = deleteNode(root, 70);
    printf("In-order traversal after deleting 70: ");
    inorder(root); // Expected: 30 40 60 80
    printf("\n\n");

    // Try to delete a non-existent node
    printf("Attempting to delete non-existent node 99.\n");
    root = deleteNode(root, 99);
    printf("In-order traversal after attempting to delete 99: ");
    inorder(root); // Should be unchanged: 30 40 60 80
    printf("\n\n");

    // Note: In a real-world application, you'd also want a function to free all
    // allocated memory for the tree when it's no longer needed to prevent memory leaks.
    // (e.g., a post-order traversal to free nodes)

    return 0;
}
