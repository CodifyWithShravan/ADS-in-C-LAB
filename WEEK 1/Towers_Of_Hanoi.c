#include <stdio.h>

// C recursive function to solve the tower of hanoi puzzle
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    // Base Case: If there is only one disk, move it directly
    if (n == 1) {
        printf("\n Move disk 1 from rod %c to rod %c", from_rod, to_rod);
        return;
    }

    // Step 1: Move n-1 disks from the source (from_rod) to the auxiliary (aux_rod)
    // The destination rod (to_rod) acts as the helper/auxiliary in this step.
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);

    // Step 2: Move the nth disk (largest) from source (from_rod) to destination (to_rod)
    printf("\n Move disk %d from rod %c to rod %c", n, from_rod, to_rod);

    // Step 3: Move the n-1 disks from the auxiliary (aux_rod) to the destination (to_rod)
    // The source rod (from_rod) now acts as the helper/auxiliary.
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

// Driver program to test the function
int main() {
    int n; // Number of disks

    printf("Enter the number of disks: ");
    scanf("%d", &n);

    // A, C, B are the names of the rods
    printf("The sequence of moves involved in the Tower of Hanoi are:\n");
    towerOfHanoi(n, 'A', 'C', 'B');
    
    printf("\n"); // For a clean new line at the end
    
    return 0;
}