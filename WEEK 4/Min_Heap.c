#include <stdio.h>
#include <stdlib.h> // Required for malloc, free (though not used in this fixed-size array example)

#define MAX_SIZE 100 // Define the maximum capacity of the heap

// Global array to store the min-heap elements
int minHeap[MAX_SIZE];
// Global variable to keep track of the current number of elements in the heap
int heapSize = 0;

// Helper function to swap two integer values.
// This is crucial for maintaining heap properties.
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the min-heap property by moving an element upwards.
// This is called after an insertion to ensure the new element is in its correct place.
void heapifyUp(int index) {
    // Continue as long as the current element is not the root (index > 0)
    // and it's smaller than its parent.
    while (index > 0 && minHeap[index] < minHeap[(index - 1) / 2]) {
        // Swap the current element with its parent
        swap(&minHeap[index], &minHeap[(index - 1) / 2]);
        // Move up to the parent's index
        index = (index - 1) / 2;
    }
}

// Function to maintain the min-heap property by moving an element downwards.
// This is called after a deletion (specifically, replacing the root) to restore the heap.
void heapifyDown(int index) {
    int smallest = index; // Assume the current node is the smallest
    int leftChild = 2 * index + 1; // Calculate index of left child
    int rightChild = 2 * index + 2; // Calculate index of right child

    // Check if the left child exists and is smaller than the current smallest
    if (leftChild < heapSize && minHeap[leftChild] < minHeap[smallest]) {
        smallest = leftChild;
    }

    // Check if the right child exists and is smaller than the current smallest
    if (rightChild < heapSize && minHeap[rightChild] < minHeap[smallest]) {
        smallest = rightChild;
    }

    // If the smallest element is not the current node, swap them
    // and recursively call heapifyDown on the swapped position.
    if (smallest != index) {
        swap(&minHeap[index], &minHeap[smallest]);
        heapifyDown(smallest);
    }
}

// Function to insert a new element into the min-heap.
void insertMinHeap(int value) {
    // Check if the heap is full before inserting
    if (heapSize >= MAX_SIZE) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }
    // Add the new element to the end of the array
    minHeap[heapSize] = value;
    // Restore heap property by moving the new element up
    heapifyUp(heapSize);
    // Increment the heap size
    heapSize++;
}

// Function to delete the minimum element (which is always at the root) from the min-heap.
int deleteMinHeap() {
    // Check if the heap is empty before deleting
    if (heapSize <= 0) {
        printf("Heap is empty. Cannot delete.\n");
        return -1; // Return -1 or throw an error for an empty heap
    }
    // Store the minimum value (root) to return later
    int minVal = minHeap[0];
    // Replace the root with the last element of the heap
    minHeap[0] = minHeap[heapSize - 1];
    // Decrement the heap size
    heapSize--;
    // Restore heap property by moving the new root down
    heapifyDown(0);
    return minVal; // Return the deleted minimum value
}

// Function to print all elements currently in the min-heap.
void printMinHeap() {
    printf("Min-Heap elements: ");
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");
}

int main() {
    printf("--- Min-Heap Operations ---\n");
    insertMinHeap(10);
    insertMinHeap(5);
    insertMinHeap(15);
    insertMinHeap(2);
    insertMinHeap(20);
    printMinHeap(); // Expected: 2 5 15 10 20 (order might vary beyond heap property)

    printf("Deleting min element...\n");
    printf("Deleted min element: %d\n", deleteMinHeap()); // Should be 2
    printMinHeap(); // Expected: 5 10 15 20 (order might vary beyond heap property)

    insertMinHeap(1);
    printMinHeap(); // Expected: 1 10 5 20 15 (order might vary beyond heap property)

    printf("Deleting min element...\n");
    printf("Deleted min element: %d\n", deleteMinHeap()); // Should be 1
    printMinHeap(); // Expected: 5 10 15 20 (order might vary beyond heap property)

    return 0;
}
