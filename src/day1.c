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
    FILE *file = fopen("numbers", "r");
    if (!file) {
        printf("Could not open file\n");
        return 1;
    }

    int left[1000], right[1000]; // Adjust size as needed
    int left_size = 0, right_size = 0;

    // Read the two lists of numbers from the file
    while (fscanf(file, "%d", &left[left_size]) != EOF && fscanf(file, "%d", &right[right_size]) != EOF) {
        left_size++;
        right_size++;
    }

    fclose(file);

    // Ensure the lists are of the same size
    if (left_size != right_size) {
        printf("The two lists must have the same number of elements.\n");
        return 1;
    }

    // Calculate and print the total distance
    int total_distance = calculate_total_distance(left, right, left_size);
    printf("Total distance between the lists: %d\n", total_distance);

    return 0;
}
