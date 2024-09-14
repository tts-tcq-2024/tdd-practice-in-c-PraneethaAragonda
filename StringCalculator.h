#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUMBER 1000

// Function Declaration
char* replace_with_commas(const char* input, const char* delimiter);
char* find_delimiter(const char* input);
void find_negatives(const char* updated_input);
int find_sum(const char* updated_input);
int add(const char* input);

// Helper function to replace delimiters with commas
char* replace_with_commas(const char* input, const char* delimiter) {
    char* result = strdup(input);
    char* p = result;
    while (*p) {
        if (*p == '\n' || strchr(delimiter, *p)) {
            *p = ',';
        }
        p++;
    }
    return result;
}

// Helper function to find the delimiter and format the string
char* find_delimiter(const char* input) {
    char* delimiter = ",";
    char* numbers_str = strdup(input);
    if (strncmp(input, "//", 2) == 0) {
        char* newline_pos = strchr(numbers_str, '\n');
        if (newline_pos) {
            *newline_pos = '\0';
            delimiter = numbers_str + 2;
            numbers_str = newline_pos + 1;
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
