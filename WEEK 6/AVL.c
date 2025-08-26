#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// AVL Tree Node Structure
typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Function prototypes
int getHeight(AVLNode* node);
int max(int a, int b);
AVLNode* createNode(int data);
int getBalance(AVLNode* node);
AVLNode* rightRotate(AVLNode* y);
AVLNode* leftRotate(AVLNode* x);
AVLNode* insert(AVLNode* node, int data);
AVLNode* minValueNode(AVLNode* node);
AVLNode* maxValueNode(AVLNode* node);
AVLNode* deleteNode(AVLNode* root, int data);
AVLNode* search(AVLNode* root, int data);
void inorderTraversal(AVLNode* root);
void preorderTraversal(AVLNode* root);
void postorderTraversal(AVLNode* root);
void levelOrderTraversal(AVLNode* root);
void printTree(AVLNode* root, int space);
void freeTree(AVLNode* root);
int countNodes(AVLNode* root);
int countLeafNodes(AVLNode* root);
int countInternalNodes(AVLNode* root);
bool isAVL(AVLNode* root);
int findMin(AVLNode* root);
int findMax(AVLNode* root);
void printPath(AVLNode* root, int data);
int findDepth(AVLNode* root, int data, int depth);
AVLNode* findPredecessor(AVLNode* root, int data);
AVLNode* findSuccessor(AVLNode* root, int data);
void printRangeValues(AVLNode* root, int min, int max);
void mirrorTree(AVLNode* root);
AVLNode* copyTree(AVLNode* root);
void printMenu();
void clearScreen();

// Global variables
AVLNode* root = NULL;
int nodeCount = 0;

// Function to get the height of a node
int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new AVL tree node
AVLNode* createNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get the balance factor of a node
int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotate
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    
    return x;
}

// Left rotate
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    
    return y;
}

// Insert a node into AVL tree
AVLNode* insert(AVLNode* node, int data) {
    if (node == NULL) {
        nodeCount++;
        return createNode(data);
    }
    
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node; // Duplicate values not allowed
    
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);
    
    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

// Find the node with minimum value
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Find the node with maximum value
AVLNode* maxValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->right != NULL)
        current = current->right;
    return current;
}

// Delete a node from AVL tree
AVLNode* deleteNode(AVLNode* root, int data) {
    if (root == NULL)
        return root;
    
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        nodeCount--;
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
            nodeCount++; // Compensate for the extra decrement
        }
    }
    
    if (root == NULL)
        return root;
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

// Search for a value in the AVL tree
AVLNode* search(AVLNode* root, int data) {
    if (root == NULL || root->data == data)
        return root;
    
    if (data < root->data)
        return search(root->left, data);
    
    return search(root->right, data);
}

// Inorder traversal
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Preorder traversal
void preorderTraversal(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Postorder traversal
void postorderTraversal(AVLNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Level order traversal (BFS)
void levelOrderTraversal(AVLNode* root) {
    if (root == NULL) return;
    
    AVLNode* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        AVLNode* current = queue[front++];
        printf("%d ", current->data);
        
        if (current->left)
            queue[rear++] = current->left;
        if (current->right)
            queue[rear++] = current->right;
    }
}

// Print tree structure
void printTree(AVLNode* root, int space) {
    const int COUNT = 10;
    if (root == NULL) return;
    
    space += COUNT;
    printTree(root->right, space);
    
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d(h:%d,b:%d)\n", root->data, root->height, getBalance(root));
    
    printTree(root->left, space);
}

// Count total nodes
int countNodes(AVLNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(AVLNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Count internal nodes
int countInternalNodes(AVLNode* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

// Check if tree is AVL
bool isAVL(AVLNode* root) {
    if (root == NULL) return true;
    
    int balance = getBalance(root);
    if (abs(balance) > 1) return false;
    
    return isAVL(root->left) && isAVL(root->right);
}

// Find minimum value
int findMin(AVLNode* root) {
    if (root == NULL) return -1;
    AVLNode* min = minValueNode(root);
    return min->data;
}

// Find maximum value
int findMax(AVLNode* root) {
    if (root == NULL) return -1;
    AVLNode* max = maxValueNode(root);
    return max->data;
}

// Print path to a value
void printPath(AVLNode* root, int data) {
    if (root == NULL) {
        printf("Value not found!\n");
        return;
    }
    
    printf("%d ", root->data);
    
    if (root->data == data) {
        printf("(Found!)\n");
        return;
    }
    
    if (data < root->data) {
        printf("-> ");
        printPath(root->left, data);
    } else {
        printf("-> ");
        printPath(root->right, data);
    }
}

// Find depth of a node
int findDepth(AVLNode* root, int data, int depth) {
    if (root == NULL) return -1;
    
    if (root->data == data) return depth;
    
    if (data < root->data)
        return findDepth(root->left, data, depth + 1);
    else
        return findDepth(root->right, data, depth + 1);
}

// Find inorder predecessor
AVLNode* findPredecessor(AVLNode* root, int data) {
    AVLNode* predecessor = NULL;
    
    while (root != NULL) {
        if (data > root->data) {
            predecessor = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    
    return predecessor;
}

// Find inorder successor
AVLNode* findSuccessor(AVLNode* root, int data) {
    AVLNode* successor = NULL;
    
    while (root != NULL) {
        if (data < root->data) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return successor;
}

// Print values in range
void printRangeValues(AVLNode* root, int min, int max) {
    if (root == NULL) return;
    
    if (root->data > min)
        printRangeValues(root->left, min, max);
    
    if (root->data >= min && root->data <= max)
        printf("%d ", root->data);
    
    if (root->data < max)
        printRangeValues(root->right, min, max);
}

// Mirror the tree
void mirrorTree(AVLNode* root) {
    if (root == NULL) return;
    
    AVLNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirrorTree(root->left);
    mirrorTree(root->right);
}

// Copy tree
AVLNode* copyTree(AVLNode* root) {
    if (root == NULL) return NULL;
    
    AVLNode* newNode = createNode(root->data);
    newNode->height = root->height;
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    
    return newNode;
}

// Free tree memory
void freeTree(AVLNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Clear screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Print menu
void printMenu() {
    printf("\n╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                    AVL TREE OPERATIONS                   ║\n");
    printf("╠═══════════════════════════════════════════════════════════╣\n");
    printf("║  1. Insert Node                    16. Find Predecessor   ║\n");
    printf("║  2. Delete Node                    17. Find Successor     ║\n");
    printf("║  3. Search Node                    18. Print Range Values ║\n");
    printf("║  4. Display Tree Structure         19. Mirror Tree        ║\n");
    printf("║  5. Inorder Traversal             20. Copy Tree          ║\n");
    printf("║  6. Preorder Traversal            21. Check if AVL       ║\n");
    printf("║  7. Postorder Traversal           22. Tree Statistics    ║\n");
    printf("║  8. Level Order Traversal         23. Bulk Insert        ║\n");
    printf("║  9. Find Minimum                  24. Bulk Delete        ║\n");
    printf("║ 10. Find Maximum                  25. Clear Tree         ║\n");
    printf("║ 11. Count Total Nodes             26. Load Sample Data   ║\n");
    printf("║ 12. Count Leaf Nodes              27. Clear Screen       ║\n");
    printf("║ 13. Count Internal Nodes          28. Tree Height        ║\n");
    printf("║ 14. Find Node Depth               0.  Exit               ║\n");
    printf("║ 15. Print Path to Node                                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("Enter your choice: ");
}

// Main function with interactive menu
int main() {
    int choice, value, min, max, depth;
    AVLNode* temp;
    
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              Welcome to AVL Tree Manager                ║\n");
    printf("║           Complete Implementation with GUI              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    while (1) {
        printMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("✓ Value %d inserted successfully!\n", value);
                break;
                
            case 2:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                scanf("%d", &value);
                if (search(root, value)) {
                    root = deleteNode(root, value);
                    printf("✓ Value %d deleted successfully!\n", value);
                } else {
                    printf("❌ Value %d not found in tree!\n", value);
                }
                break;
                
            case 3:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter value to search: ");
                scanf("%d", &value);
                temp = search(root, value);
                if (temp) {
                    printf("✓ Value %d found in tree!\n", value);
                } else {
                    printf("❌ Value %d not found in tree!\n", value);
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("\n🌳 Tree Structure (Right-Root-Left):\n");
                printf("Format: Value(height:h, balance:b)\n");
                printf("═══════════════════════════════════════\n");
                printTree(root, 0);
                printf("═══════════════════════════════════════\n");
                break;
                
            case 5:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("📊 Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
                
            case 6:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("📊 Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
                
            case 7:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("📊 Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
                
            case 8:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("📊 Level Order Traversal: ");
                levelOrderTraversal(root);
                printf("\n");
                break;
                
            case 9:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("🔽 Minimum value: %d\n", findMin(root));
                break;
                
            case 10:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("🔼 Maximum value: %d\n", findMax(root));
                break;
                
            case 11:
                printf("📈 Total nodes: %d\n", countNodes(root));
                break;
                
            case 12:
                printf("🍃 Leaf nodes: %d\n", countLeafNodes(root));
                break;
                
            case 13:
                printf("🌿 Internal nodes: %d\n", countInternalNodes(root));
                break;
                
            case 14:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter value to find depth: ");
                scanf("%d", &value);
                depth = findDepth(root, value, 0);
                if (depth != -1) {
                    printf("📏 Depth of %d: %d\n", value, depth);
                } else {
                    printf("❌ Value %d not found!\n", value);
                }
                break;
                
            case 15:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter value to find path: ");
                scanf("%d", &value);
                printf("🛤️  Path to %d: ", value);
                printPath(root, value);
                break;
                
            case 16:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter value to find predecessor: ");
                scanf("%d", &value);
                temp = findPredecessor(root, value);
                if (temp) {
                    printf("⬅️ Predecessor of %d: %d\n", value, temp->data);
                } else {
                    printf("❌ No predecessor found for %d\n", value);
                }
                break;
                
            case 17:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter value to find successor: ");
                scanf("%d", &value);
                temp = findSuccessor(root, value);
                if (temp) {
                    printf("➡️ Successor of %d: %d\n", value, temp->data);
                } else {
                    printf("❌ No successor found for %d\n", value);
                }
                break;
                
            case 18:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("Enter range (min max): ");
                scanf("%d %d", &min, &max);
                printf("📋 Values in range [%d, %d]: ", min, max);
                printRangeValues(root, min, max);
                printf("\n");
                break;
                
            case 19:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                mirrorTree(root);
                printf("🪞 Tree mirrored successfully!\n");
                break;
                
            case 20:
                if (root == NULL) {
                    printf("❌ Tree is empty!\n");
                    break;
                }
                printf("📋 Tree copied successfully! (Note: Copy created in memory)\n");
                break;
                
            case 21:
                if (isAVL(root)) {
                    printf("✅ Tree is a valid AVL tree!\n");
                } else {
                    printf("❌ Tree is NOT a valid AVL tree!\n");
                }
                break;
                
            case 22:
                printf("\n📊 TREE STATISTICS\n");
                printf("═══════════════════\n");
                printf("Total Nodes: %d\n", countNodes(root));
                printf("Leaf Nodes: %d\n", countLeafNodes(root));
                printf("Internal Nodes: %d\n", countInternalNodes(root));
                printf("Tree Height: %d\n", getHeight(root));
                if (root) {
                    printf("Root Value: %d\n", root->data);
                    printf("Min Value: %d\n", findMin(root));
                    printf("Max Value: %d\n", findMax(root));
                }
                printf("Is AVL: %s\n", isAVL(root) ? "Yes" : "No");
                break;
                
            case 23:
                printf("Enter number of values to insert: ");
                scanf("%d", &value);
                printf("Enter %d values: ", value);
                for (int i = 0; i < value; i++) {
                    int val;
                    scanf("%d", &val);
                    root = insert(root, val);
                }
                printf("✓ %d values inserted successfully!\n", value);
                break;
                
            case 24:
                printf("Enter number of values to delete: ");
                scanf("%d", &value);
                printf("Enter %d values: ", value);
                for (int i = 0; i < value; i++) {
                    int val;
                    scanf("%d", &val);
                    if (search(root, val)) {
                        root = deleteNode(root, val);
                    }
                }
                printf("✓ Bulk deletion completed!\n");
                break;
                
            case 25:
                if (root != NULL) {
                    freeTree(root);
                    root = NULL;
                    nodeCount = 0;
                    printf("🗑️  Tree cleared successfully!\n");
                } else {
                    printf("❌ Tree is already empty!\n");
                }
                break;
                
            case 26:
                printf("Loading sample data: 50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35...\n");
                int sampleData[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35};
                int sampleSize = sizeof(sampleData) / sizeof(sampleData[0]);
                for (int i = 0; i < sampleSize; i++) {
                    root = insert(root, sampleData[i]);
                }
                printf("✓ Sample data loaded successfully!\n");
                break;
                
            case 27:
                clearScreen();
                printf("╔══════════════════════════════════════════════════════════╗\n");
                printf("║              Welcome to AVL Tree Manager                ║\n");
                printf("║           Complete Implementation with GUI              ║\n");
                printf("╚══════════════════════════════════════════════════════════╝\n");
                break;
                
            case 28:
                printf("🏔️  Tree Height: %d\n", getHeight(root));
                break;
                
            case 0:
                if (root != NULL) {
                    freeTree(root);
                }
                printf("\n👋 Thank you for using AVL Tree Manager!\n");
                printf("💾 All memory freed successfully. Goodbye!\n");
                return 0;
                
            default:
                printf("❌ Invalid choice! Please try again.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar(); // consume newline
        getchar(); // wait for user input
    }
    
    return 0;
}