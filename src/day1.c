#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to calculate the total distance
int calculate_total_distance(int *left, int *right, int size) {
    // Sort both lists
    qsort(left, size, sizeof(int), compare);
    qsort(right, size, sizeof(int), compare);

    int total_distance = 0;

    // Calculate the sum of distances
    for (int i = 0; i < size; i++) {
        total_distance += abs(left[i] - right[i]);
    }

    return total_distance;
}

int main() {
    int left[] = {3, 4, 2, 1, 3, 3};
    int right[] = {4, 3, 5, 3, 9, 3};
    int size = sizeof(left) / sizeof(left[0]);

    // Calculate and print the total distance
    int total_distance = calculate_total_distance(left, right, size);
    printf("Total distance between the lists: %d\n", total_distance);

    return 0;
}
