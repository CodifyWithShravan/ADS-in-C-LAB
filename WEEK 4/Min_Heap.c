#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Heap structure
typedef struct {
    int items[MAX_SIZE];
    int size;
} MinHeap;

// Initializes the heap
void initializeHeap(MinHeap* h) {
    h->size = 0;
}

// Swaps two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Moves an element up the heap
void heapifyUp(MinHeap* h, int index) {
    while (index > 0 && h->items[index] < h->items[(index - 1) / 2]) {
        swap(&h->items[index], &h->items[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Moves an element down the heap
void heapifyDown(MinHeap* h, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->size && h->items[left] < h->items[smallest]) {
        smallest = left;
    }
    if (right < h->size && h->items[right] < h->items[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&h->items[index], &h->items[smallest]);
        heapifyDown(h, smallest);
    }
}

// Inserts an element
void insert(MinHeap* h, int value) {
    if (h->size >= MAX_SIZE) {
        printf("Heap is full.\n");
        return;
    }
    h->items[h->size] = value;
    heapifyUp(h, h->size);
    h->size++;
}

// Deletes the minimum element
int deleteMin(MinHeap* h) {
    if (h->size <= 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    int minVal = h->items[0];
    h->items[0] = h->items[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    return minVal;
}

// Prints heap elements
void printHeap(MinHeap* h) {
    printf("Min-Heap elements: ");
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->items[i]);
    }
    printf("\n");
}

int main() {
    MinHeap myHeap;
    initializeHeap(&myHeap);

    insert(&myHeap, 10);
    insert(&myHeap, 5);
    insert(&myHeap, 15);
    printHeap(&myHeap);

    printf("Deleted min element: %d\n", deleteMin(&myHeap));
    printHeap(&myHeap);

    return 0;
}