#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBER 1000

// Helper function to check if a character is a newline or in the delimiter
int is_delimiter_or_newline(char c, const char* delimiter) {
    return (c == '\n' || strchr(delimiter, c) != NULL);
}

// Main function to replace newline and delimiter characters with commas
char* replace_with_commas(const char* input, const char* delimiter) {
    char* result = strdup(input);
    if (!result) return NULL;  // Error handling if memory allocation fails

    for (char* p = result; *p != '\0'; ++p) {
        // Replace newline or delimiter with a comma
        if (*p == '\n' || strchr(delimiter, *p)) {
            *p = ',';  // Replace character with a comma
        }
    }

    return result;
}

// Helper function to find the delimiter and format the string
char* find_delimiter(const char* input) {
    char delimiter[2] = ","; // Default delimiter
    char* numbers_str = strdup(input);
    
    if (strncmp(input, "//", 2) == 0) {
        char* newline_pos = strchr(numbers_str, '\n');
        if (newline_pos) {
            delimiter[0] = *(numbers_str + 2); // Pick custom delimiter
            numbers_str = newline_pos + 1;     // Numbers part starts after \n
        }
    }
    
    char* updated_input = replace_with_commas(numbers_str, delimiter);
    free(numbers_str);
    return updated_input;
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
