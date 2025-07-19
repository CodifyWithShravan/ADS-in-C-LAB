#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // For strcmp

// --- Tree Node Definition ---
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Unable to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// --- Queue Implementation for Level Order Traversal ---
// Note: A simple array-based queue for storing TreeNode pointers.
#define MAX_QUEUE_SIZE 100

typedef struct Queue {
    TreeNode* items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Function to create a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        perror("Unable to allocate memory for queue");
        exit(EXIT_FAILURE);
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if the queue is empty
bool isEmpty(Queue* q) {
    // Check if front has surpassed rear or if it's uninitialized
    return q->front == -1 || q->front > q->rear;
}

// Add an item to the queue
void enqueue(Queue* q, TreeNode* node) {
    if (q->rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = node;
}

// Remove an item from the queue
TreeNode* dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return NULL;
    }
    TreeNode* item = q->items[q->front];
    q->front++;
    // No need to reset here, isEmpty handles the logic
    return item;
}

// Get the current size of the queue
int queueSize(Queue* q) {
    if (isEmpty(q)) return 0;
    return q->rear - q->front + 1;
}

// --- Zigzag Traversal Implementation ---

// Helper function to reverse an array
void reverseArray(int* arr, int size) {
    int start = 0;
    int end = size - 1;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void zigzagLevelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty. Nothing to traverse.\n");
        return;
    }

    Queue* queue = createQueue();
    enqueue(queue, root);
    bool leftToRight = true;

    printf("[\n");
    while (!isEmpty(queue)) {
        int levelSize = queueSize(queue);
        int* currentLevel = (int*)malloc(levelSize * sizeof(int));
        if (!currentLevel) {
            perror("Failed to allocate memory for level array");
            return;
        }

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = dequeue(queue);
            currentLevel[i] = node->val;

            if (node->left != NULL) enqueue(queue, node->left);
            if (node->right != NULL) enqueue(queue, node->right);
        }

        if (!leftToRight) {
            reverseArray(currentLevel, levelSize);
        }

        printf("  [");
        for (int i = 0; i < levelSize; i++) {
            printf("%d", currentLevel[i]);
            if (i < levelSize - 1) printf(", ");
        }
        printf("]\n");

        leftToRight = !leftToRight;
        free(currentLevel);
    }
    printf("]\n");
    free(queue);
}

// --- Interactive Tree Building and Cleanup ---

// Function to free all nodes in a tree to prevent memory leaks
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Function to build a tree interactively from user input
TreeNode* buildTreeInteractive() {
    char valStr[10];
    printf("\n--- Build Your Binary Tree ---\n");
    printf("Enter node values level by level. Use 'N' or 'n' for null nodes.\n");
    printf("Enter the root value: ");
    scanf("%s", valStr);

    if (strcmp(valStr, "N") == 0 || strcmp(valStr, "n") == 0) {
        return NULL;
    }

    TreeNode* root = createNode(atoi(valStr));
    Queue* q = createQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        TreeNode* current = dequeue(q);

        // Prompt for left child
        printf("Enter left child for %d (or 'N' for null): ", current->val);
        scanf("%s", valStr);
        if (strcmp(valStr, "N") != 0 && strcmp(valStr, "n") != 0) {
            current->left = createNode(atoi(valStr));
            enqueue(q, current->left);
        }

        // Prompt for right child
        printf("Enter right child for %d (or 'N' for null): ", current->val);
        scanf("%s", valStr);
        if (strcmp(valStr, "N") != 0 && strcmp(valStr, "n") != 0) {
            current->right = createNode(atoi(valStr));
            enqueue(q, current->right);
        }
    }
    free(q);
    return root;
}


// --- Main Function ---
int main() {
    char choice;
    do {
        TreeNode* root = buildTreeInteractive();

        printf("\n--- Traversal Result ---\n");
        zigzagLevelOrder(root);

        // Clean up the dynamically allocated tree
        freeTree(root);

        printf("\nDo you want to build another tree? (y/n): ");
        // Note: The space before %c is important to consume any leftover newline/whitespace
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("Exiting program.\n");
    return 0;
}