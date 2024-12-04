#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to check if the report is safe
bool is_safe_report(int *report, int size) {
    bool is_increasing = true;
    bool is_decreasing = true;

    // Check differences and if it's increasing or decreasing
    for (int i = 0; i < size - 1; i++) {
        int diff = abs(report[i] - report[i + 1]);

        // If difference is not between 1 and 3, the report is unsafe
        if (diff < 1 || diff > 3) {
            return false;
        }

        // Track if it's increasing or decreasing
        if (report[i] < report[i + 1]) {
            is_decreasing = false;  // Not decreasing
        }
        if (report[i] > report[i + 1]) {
            is_increasing = false;  // Not increasing
        }
    }

    // Report is safe if it's either increasing or decreasing
    return is_increasing || is_decreasing;
}

// Function to check if removing one level makes the report safe
bool can_be_safe_by_removing_one(int *report, int size) {
    for (int i = 0; i < size; i++) {
        int modified_report[8];
        int modified_size = 0;

        // Copy all levels except the one to be removed
        for (int j = 0; j < size; j++) {
            if (j != i) {
                modified_report[modified_size++] = report[j];
            }
        }

        // Check if the modified report is safe
        if (is_safe_report(modified_report, modified_size)) {
            return true;
        }
    }

    return false;
}

// Function to count the number of safe reports, considering the Problem Dampener
int count_safe_reports(FILE *file) {
    int safe_count = 0;
    char line[50];  // Buffer to read each line (assuming max line length is 50 characters)

    while (fgets(line, sizeof(line), file)) {
        int report[8];  // Array to store the report levels (max 8 numbers)
        int size = 0;

        // Tokenize the line into numbers
        char *token = strtok(line, " \n");
        while (token != NULL) {
            report[size++] = atoi(token);  // Convert the token to an integer
            token = strtok(NULL, " \n");    // Get the next token
        }

        // Check if the current report is safe by the original rules or if removing one level makes it safe
        if (is_safe_report(report, size) || can_be_safe_by_removing_one(report, size)) {
            safe_count++;
        }
    }

    return safe_count;
}

int main() {
    FILE *file = fopen("day2", "r");  // Open the input file

    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    int safe_reports = count_safe_reports(file);
    printf("Number of safe reports: %d\n", safe_reports);

    fclose(file);  // Close the file
    return 0;
}
