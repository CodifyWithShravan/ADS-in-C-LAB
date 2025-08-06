#include <stdio.h>
#include <stdlib.h>

// A comparison function for qsort to sort in ascending order
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findKthElements(int arr[], int n, int k) {
    // Check if k is a valid index
    if (k < 1 || k > n) {
        printf("Invalid value of K.\n");
        return;
    }

    // Sort the array in ascending order
    qsort(arr, n, sizeof(int), compare);

    // Kth smallest element is at index k-1
    printf("The %dth smallest element is: %d\n", k, arr[k - 1]);

    // Kth largest element is at index n-k
    printf("The %dth largest element is: %d\n", k, arr[n - k]);
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    findKthElements(arr, n, k);

    return 0;
}