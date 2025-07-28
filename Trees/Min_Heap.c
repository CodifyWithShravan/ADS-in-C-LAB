#include <stdio.h>
#include <stdlib.h> // For malloc and free, though we'll use a fixed-size array for simplicity here.

// Define a maximum size for the heap to keep it simple for array-based implementation
#define MAX_HEAP_SIZE 100

// Structure to represent a Min-Heap
typedef struct {
    int arr[MAX_HEAP_SIZE]; // Array to store heap elements
    int size;               // Current number of elements in the heap
} MinHeap;

// --- Utility Functions ---

// Initialize a Min-Heap
void initMinHeap(MinHeap *heap) {
    heap->size = 0;
    printf("Min-Heap initialized.\n");
}

// Swap two integer values
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// --- Heap Operations ---

// Heapify Up: Restores the heap property by bubbling up an element from 'index'
void heapifyUp(MinHeap *heap, int index) {
    int parent = (index - 1) / 2; // Calculate parent index

    // Continue bubbling up as long as the current element is smaller than its parent
    // and we haven't reached the root (index > 0)
    while (index > 0 && heap->arr[parent] > heap->arr[index]) {
        swap(&heap->arr[parent], &heap->arr[index]); // Swap with parent
        index = parent;                               // Move to the parent's position
        parent = (index - 1) / 2;                     // Recalculate new parent
    }
}

// Heapify Down: Restores the heap property by bubbling down an element from 'index'
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;        // Assume current node is the smallest
    int leftChild = 2 * index + 1; // Calculate left child index
    int rightChild = 2 * index + 2; // Calculate right child index

    // Check if left child exists and is smaller than the current smallest
    if (leftChild < heap->size && heap->arr[leftChild] < heap->arr[smallest]) {
        smallest = leftChild;
    }

    // Check if right child exists and is smaller than the current smallest
    if (rightChild < heap->size && heap->arr[rightChild] < heap->arr[smallest]) {
        smallest = rightChild;
    }

    // If the smallest is not the current node, swap and continue heapifying down
    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapifyDown(heap, smallest); // Recursively call heapifyDown on the swapped child
    }
}

// Insert a value into the Min-Heap
void insertMinHeap(MinHeap *heap, int value) {
    if (heap->size >= MAX_HEAP_SIZE) {
        printf("Error: Heap is full. Cannot insert %d.\n", value);
        return;
    }

    // Add the new element to the end of the array
    heap->arr[heap->size] = value;
    heap->size++; // Increment heap size

    // Restore heap property by bubbling up the newly added element
    heapifyUp(heap, heap->size - 1);
    printf("%d inserted into the heap.\n", value);
}

// Extract (remove) the minimum element from the Min-Heap (which is always at the root)
int extractMin(MinHeap *heap) {
    if (heap->size <= 0) {
        printf("Error: Heap is empty. Cannot extract minimum.\n");
        return -1; // Return a sentinel value for error, or you could exit/throw an error
    }

    // If only one element, just remove and return it
    if (heap->size == 1) {
        heap->size--;
        printf("Extracted: %d\n", heap->arr[0]);
        return heap->arr[0];
    }

    // Store the root (minimum) element to return later
    int root = heap->arr[0];

    // Replace the root with the last element in the heap
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--; // Decrement heap size

    // Restore heap property by bubbling down the new root
    heapifyDown(heap, 0);

    printf("Extracted: %d\n", root);
    return root;
}

// Get the minimum element without removing it
int peekMin(MinHeap *heap) {
    if (heap->size <= 0) {
        printf("Error: Heap is empty. No minimum element.\n");
        return -1;
    }
    printf("Minimum element (peek): %d\n", heap->arr[0]);
    return heap->arr[0];
}

// Display the elements of the heap (as they are stored in the array)
void printHeap(MinHeap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }
    printf("Heap elements (array representation): ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

// --- User Interface Functions ---

// Display the main menu
void displayMenu() {
    printf("\n--- Min-Heap Operations ---\n");
    printf("1. Insert element\n");
    printf("2. Extract Minimum element\n");
    printf("3. Peek Minimum element\n");
    printf("4. Display Heap\n");
    printf("5. Exit\n");
    printf("---------------------------\n");
    printf("Enter your choice: ");
}

int main() {
    MinHeap myHeap;
    initMinHeap(&myHeap); // Initialize the heap

    int choice;
    int value;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear invalid input from buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input. Please enter an integer.\n");
                    while (getchar() != '\n');
                    break;
                }
                insertMinHeap(&myHeap, value);
                break;
            case 2:
                extractMin(&myHeap);
                break;
            case 3:
                peekMin(&myHeap);
                break;
            case 4:
                printHeap(&myHeap);
                break;
            case 5:
                printf("Exiting Min-Heap program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}