#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBER 1000

/char* replace_with_commas(const char* input, const char* delimiter) {
    char* result = strdup(input);  // Create a copy of the input string
    if (!result) return NULL;      // Check if memory allocation fails

    char* p = result;
    while (*p) {
        if (strchr(delimiter, *p) || *p == '\n') {
            *p = ',';  // Replace the character with a comma
        }
        p++;
    }

    return result;
}

// Helper function to check for negative numbers
void find_negatives(const char* updated_input) {
    char* input_copy = strdup(updated_input);
    char* token = strtok(input_copy, ",");
    while (token) {
        if (atoi(token) < 0) {
            free(input_copy);
            fprintf(stderr, "Error: Negatives not allowed\n");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, ",");
    }
    free(input_copy);
}

// Helper function to calculate the sum of numbers
int find_sum(const char* updated_input) {
    char* input_copy = strdup(updated_input);
    char* token = strtok(input_copy, ",");
    int sum = 0;
    while (token) {
        int number = atoi(token);
        if (number <= MAX_NUMBER) {
            sum += number;
        }
        token = strtok(NULL, ",");
    }
    free(input_copy);
    return sum;
}

// Main add function
int add(const char* input) {
    if (input == NULL || strlen(input) == 0) {
        return 0;
    }
    char* updated_input = find_delimiter(input);
    find_negatives(updated_input);
    int sum = find_sum(updated_input);
    free(updated_input);
    return sum;
}

// Main function for testing
int main() {
    // Example test cases
    const char* test_cases[] = {
        "",
        "praneetha",
        "1",
        "1,2",
        "1\n2,3",
        "//;\n1;2",
        "2+1001",
        "2+1000"
    };
    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        printf("Input: \"%s\" -> Result: %d\n", test_cases[i], add(test_cases[i]));
    }
    return 0;
}
