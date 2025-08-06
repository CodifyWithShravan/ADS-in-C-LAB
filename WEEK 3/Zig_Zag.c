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

// Creates a new tree node
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Memory allocation failed for tree node");
        exit(EXIT_FAILURE);
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// --- Queue Implementation ---
#define MAX_QUEUE_SIZE 100

typedef struct Queue {
    TreeNode* items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Creates and initializes a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        perror("Memory allocation failed for queue");
        exit(EXIT_FAILURE);
    }
    q->front = -1;
    q->rear = -1;
    return q;
}

// Checks if the queue is empty
bool isEmpty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

// Adds a node to the queue
void enqueue(Queue* q, TreeNode* node) {
    if (q->rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full, cannot enqueue!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = node;
}

// Removes and returns a node from the queue
TreeNode* dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty, cannot dequeue!\n");
        return NULL;
    }
    TreeNode* item = q->items[q->front];
    q->front++;
    return item;
}

// Gets the current number of items in the queue
int queueSize(Queue* q) {
    if (isEmpty(q)) return 0;
    return q->rear - q->front + 1;
}

// --- Zigzag Traversal ---

// Reverses an array of integers
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

// Performs zigzag level order traversal and prints the result
void zigzagLevelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Queue* queue = createQueue();
    enqueue(queue, root);
    bool leftToRight = true;

    printf("[\n"); // Start of overall output
    while (!isEmpty(queue)) {
        int levelSize = queueSize(queue);
        int* currentLevel = (int*)malloc(levelSize * sizeof(int));
        if (!currentLevel) {
            perror("Memory allocation failed for level array");
            // Clean up queue before exiting or returning
            while(!isEmpty(queue)) {
                dequeue(queue);
            }
            free(queue);
            exit(EXIT_FAILURE);
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

        printf("  ["); // Start of current level output
        for (int i = 0; i < levelSize; i++) {
            printf("%d", currentLevel[i]);
            if (i < levelSize - 1) printf(", ");
        }
        printf("]\n"); // End of current level output

        leftToRight = !leftToRight;
        free(currentLevel); // Free memory for current level array
    }
    printf("]\n"); // End of overall output
    free(queue); // Free the queue structure itself
}

// --- Tree Building and Cleanup ---

// Frees all nodes in the tree recursively
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Builds a binary tree interactively from user input
TreeNode* buildTreeInteractive() {
    char valStr[10];
    printf("\n--- Build Binary Tree ---\n");
    printf("Enter node values level by level. Use 'N' for null.\n");
    printf("Root value: ");
    scanf("%s", valStr);

    if (strcmp(valStr, "N") == 0 || strcmp(valStr, "n") == 0) {
        return NULL;
    }

    TreeNode* root = createNode(atoi(valStr));
    Queue* q = createQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        TreeNode* current = dequeue(q);

        printf("Left child of %d (or 'N'): ", current->val);
        scanf("%s", valStr);
        if (strcmp(valStr, "N") != 0 && strcmp(valStr, "n") != 0) {
            current->left = createNode(atoi(valStr));
            enqueue(q, current->left);
        }

        printf("Right child of %d (or 'N'): ", current->val);
        scanf("%s", valStr);
        if (strcmp(valStr, "N") != 0 && strcmp(valStr, "n") != 0) {
            current->right = createNode(atoi(valStr));
            enqueue(q, current->right);
        }
    }
    free(q); // Free the queue structure
    return root;
}

// --- Main Function ---
int main() {
    char choice;
    do {
        TreeNode* root = buildTreeInteractive();

        printf("\n--- Zigzag Traversal Result ---\n");
        zigzagLevelOrder(root);

        // Clean up the dynamically allocated tree
        freeTree(root);

        printf("\nBuild another tree? (y/n): ");
        scanf(" %c", &choice); // Space before %c to consume newline

    } while (choice == 'y' || choice == 'Y');

    printf("Exiting.\n");
    return 0;
}
