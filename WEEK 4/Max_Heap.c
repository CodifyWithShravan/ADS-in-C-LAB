#include <stdio.h>
#include <stdlib.h> // Required for malloc, free (though not used in this fixed-size array example)

#define MAX_SIZE 100 // Define the maximum capacity of the heap

// Global array to store the max-heap elements
int maxHeap[MAX_SIZE];
// Global variable to keep track of the current number of elements in the heap
int heapSize = 0;

// Helper function to swap two integer values.
// This is crucial for maintaining heap properties.
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the max-heap property by moving an element upwards.
// This is called after an insertion to ensure the new element is in its correct place.
void heapifyUp(int index) {
    // Continue as long as the current element is not the root (index > 0)
    // and it's larger than its parent.
    while (index > 0 && maxHeap[index] > maxHeap[(index - 1) / 2]) {
        // Swap the current element with its parent
        swap(&maxHeap[index], &maxHeap[(index - 1) / 2]);
        // Move up to the parent's index
        index = (index - 1) / 2;
    }
}

// Function to maintain the max-heap property by moving an element downwards.
// This is called after a deletion (specifically, replacing the root) to restore the heap.
void heapifyDown(int index) {
    int largest = index; // Assume the current node is the largest
    int leftChild = 2 * index + 1; // Calculate index of left child
    int rightChild = 2 * index + 2; // Calculate index of right child

    // Check if the left child exists and is larger than the current largest
    if (leftChild < heapSize && maxHeap[leftChild] > maxHeap[largest]) {
        largest = leftChild;
    }

    // Check if the right child exists and is larger than the current largest
    if (rightChild < heapSize && maxHeap[rightChild] > maxHeap[largest]) {
        largest = rightChild;
    }

    // If the largest element is not the current node, swap them
    // and recursively call heapifyDown on the swapped position.
    if (largest != index) {
        swap(&maxHeap[index], &maxHeap[largest]);
        heapifyDown(largest);
    }
}

// Function to insert a new element into the max-heap.
void insertMaxHeap(int value) {
    // Check if the heap is full before inserting
    if (heapSize >= MAX_SIZE) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }
    // Add the new element to the end of the array
    maxHeap[heapSize] = value;
    // Restore heap property by moving the new element up
    heapifyUp(heapSize);
    // Increment the heap size
    heapSize++;
}

// Function to delete the maximum element (which is always at the root) from the max-heap.
int deleteMaxHeap() {
    // Check if the heap is empty before deleting
    if (heapSize <= 0) {
        printf("Heap is empty. Cannot delete.\n");
        return -1; // Return -1 or throw an error for an empty heap
    }
    // Store the maximum value (root) to return later
    int maxVal = maxHeap[0];
    // Replace the root with the last element of the heap
    maxHeap[0] = maxHeap[heapSize - 1];
    // Decrement the heap size
    heapSize--;
    // Restore heap property by moving the new root down
    heapifyDown(0);
    return maxVal; // Return the deleted maximum value
}

// Function to print all elements currently in the max-heap.
void printMaxHeap() {
    printf("Max-Heap elements: ");
    for (int i = 0; i < heapSize; i++) {
        printf("%d ", maxHeap[i]);
    }
    printf("\n");
}

int main() {
    printf("--- Max-Heap Operations ---\n");
    insertMaxHeap(10);
    insertMaxHeap(5);
    insertMaxHeap(15);
    insertMaxHeap(2);
    insertMaxHeap(20);
    printMaxHeap(); // Expected: 20 15 10 2 5 (order might vary beyond heap property)

    printf("Deleting max element...\n");
    printf("Deleted max element: %d\n", deleteMaxHeap()); // Should be 20
    printMaxHeap(); // Expected: 15 5 10 2 (order might vary beyond heap property)

    insertMaxHeap(25);
    printMaxHeap(); // Expected: 25 15 10 2 5 (order might vary beyond heap property)

    printf("Deleting max element...\n");
    printf("Deleted max element: %d\n", deleteMaxHeap()); // Should be 25
    printMaxHeap(); // Expected: 15 5 10 2 (order might vary beyond heap property)

    return 0;
}
