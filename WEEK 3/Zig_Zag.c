#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node and Queue structures
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Queue {
    TreeNode* items[100];
    int front;
    int rear;
} Queue;

// Queue operations
void initialize(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

void enqueue(Queue* q, TreeNode* node) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = node;
}

TreeNode* dequeue(Queue* q) {
    if (isEmpty(q)) {
        return NULL;
    }
    return q->items[q->front++];
}

// Reverses an array
void reverse(int* arr, int size) {
    int start = 0, end = size - 1;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// Zigzag Traversal
void zigzagTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    Queue q;
    initialize(&q);
    enqueue(&q, root);
    bool leftToRight = true;

    printf("[\n");
    while (!isEmpty(&q)) {
        int levelSize = q.rear - q.front + 1;
        int levelVals[levelSize];

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = dequeue(&q);
            levelVals[i] = node->val;

            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }

        if (!leftToRight) {
            reverse(levelVals, levelSize);
        }

        printf("  [");
        for (int i = 0; i < levelSize; i++) {
            printf("%d", levelVals[i]);
            if (i < levelSize - 1) printf(", ");
        }
        printf("]\n");

        leftToRight = !leftToRight;
    }
    printf("]\n");
}

int main() {
    // Manually create a sample binary tree
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = 3;
    root->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->left->val = 9;
    root->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->val = 20;
    root->left->left = root->left->right = NULL;
    root->right->left = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->left->val = 15;
    root->right->right = (TreeNode*)malloc(sizeof(TreeNode));
    root->right->right->val = 7;
    root->right->left->left = root->right->left->right = NULL;
    root->right->right->left = root->right->right->right = NULL;

    zigzagTraversal(root);

    // Free allocated memory
    free(root->right->right);
    free(root->right->left);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}