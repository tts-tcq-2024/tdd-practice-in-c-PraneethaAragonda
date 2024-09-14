#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUMBER 1000

// Function Declaration
int add(const char* input);

// Helper function to parse numbers from the input string
int parse_numbers(const char* input, const char* delimiters) {
    int sum = 0;
    char* input_copy = strdup(input);  // Make a mutable copy of the input
    char* token = strtok(input_copy, delimiters);
    
    while (token != NULL) {
        int number = atoi(token);  // Convert the token to an integer
        if (number <= MAX_NUMBER) {  // Ignore numbers greater than 1000
            sum += number;  // Add to sum if the number is less than or equal to 1000
        }
        token = strtok(NULL, delimiters);  // Get the next token
    }

    free(input_copy);  // Free the dynamically allocated memory
    return sum;
}

// Refactored add function with CCN = 3
int add(const char* input) {
    // If input is NULL or empty, return 0 immediately
    if (input == NULL || strlen(input) == 0) {
        return 0;
    }

    // Handle custom delimiter if input starts with "//"
    const char* newline_pos = (strncmp(input, "//", 2) == 0) ? strchr(input, '\n') : NULL;
    if (newline_pos) {
        return parse_numbers(newline_pos + 1, input + 2);  // Parse using custom delimiter
    }

    // Default case: use comma and newline as delimiters
    return parse_numbers(input, ",\n");
}
