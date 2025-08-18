#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Heap structure to encapsulate data and size
typedef struct {
    int items[MAX_SIZE];
    int size;
} MaxHeap;

// Initializes the heap
void initializeHeap(MaxHeap* h) {
    h->size = 0;
}

// Swaps two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Moves an element up the heap to maintain the max-heap property
void heapifyUp(MaxHeap* h, int index) {
    while (index > 0 && h->items[index] > h->items[(index - 1) / 2]) {
        swap(&h->items[index], &h->items[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Moves an element down the heap to maintain the max-heap property
void heapifyDown(MaxHeap* h, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->items[left] > h->items[largest]) {
        largest = left;
    }
    if (right < h->size && h->items[right] > h->items[largest]) {
        largest = right;
    }

    if (largest != index) {
        swap(&h->items[index], &h->items[largest]);
        heapifyDown(h, largest);
    }
}

// Inserts an element into the heap
void insert(MaxHeap* h, int value) {
    if (h->size >= MAX_SIZE) {
        printf("Heap is full.\n");
        return;
    }
    h->items[h->size] = value;
    heapifyUp(h, h->size);
    h->size++;
}

// Deletes the maximum element (root) from the heap
int deleteMax(MaxHeap* h) {
    if (h->size <= 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    int maxVal = h->items[0];
    h->items[0] = h->items[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return maxVal;
}

// Prints the heap elements
void printHeap(MaxHeap* h) {
    printf("Heap elements: ");
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->items[i]);
    }
    printf("\n");
}

int main() {
    MaxHeap myHeap;
    initializeHeap(&myHeap);

    insert(&myHeap, 10);
    insert(&myHeap, 5);
    insert(&myHeap, 15);
    printHeap(&myHeap);

    printf("Deleted max element: %d\n", deleteMax(&myHeap));
    printHeap(&myHeap);

    return 0;
}