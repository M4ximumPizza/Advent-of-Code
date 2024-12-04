#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a string contains a valid mul(X,Y) and return the result
int extract_mul_result(const char *str, int *start_idx) {
    int x = 0, y = 0, i = *start_idx;

    // Check for "mul("
    if (strncmp(&str[i], "mul(", 4) != 0) {
        return 0; // Not a valid mul instruction
    }
    i += 4; // Skip past "mul("

    // Extract the first number (X)
    if (!isdigit(str[i])) return 0;
    while (isdigit(str[i])) {
        x = x * 10 + (str[i++] - '0');
    }

    // Check for comma
    if (str[i++] != ',') return 0;

    // Extract the second number (Y)
    if (!isdigit(str[i])) return 0;
    while (isdigit(str[i])) {
        y = y * 10 + (str[i++] - '0');
    }

    // Check for closing parenthesis
    if (str[i++] != ')') return 0;

    // Update start index to continue after this mul instruction
    *start_idx = i;

    // Return the result of the multiplication
    return x * y;
}

// Function to check for "do()" or "don't()" instructions
int extract_control_instruction(const char *str, int *start_idx) {
    if (strncmp(&str[*start_idx], "do()", 4) == 0) {
        *start_idx += 4;
        return 1; // Enable mul
    }
    if (strncmp(&str[*start_idx], "don't()", 7) == 0) {
        *start_idx += 7;
        return 0; // Disable mul
    }
    return -1; // No control instruction
}

int main() {
    const char *filename = "day3";

    // Open the file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Read the entire file into memory
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *input = malloc(file_size + 1);
    if (!input) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fread(input, 1, file_size, file);
    input[file_size] = '\0'; // Null-terminate the string
    fclose(file);

    int sum = 0;
    int i = 0;
    int result;
    int mul_enabled = 1; // Mul instructions are initially enabled

    // Parse the input string
    while (input[i] != '\0') {
        // Check for control instructions
        int control = extract_control_instruction(input, &i);
        if (control != -1) {
            mul_enabled = control;
            continue;
        }

        // Check for mul instructions
        result = extract_mul_result(input, &i);
        if (result > 0 && mul_enabled) {
            sum += result;
        } else {
            i++; // Move to the next character if no valid instruction found
        }
    }

    // Output the sum of all valid mul results
    printf("Sum of all valid and enabled mul results: %d\n", sum);

    // Free allocated memory
    free(input);

    return 0;
}
