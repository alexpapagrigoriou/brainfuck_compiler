#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CODE_CAPACITY 128

static char *add_command(size_t *size, size_t *capacity, char *code, char c, int *comma_counter) {
    if (*size >= *capacity) {
        *capacity *= 2;
        char *tmp_code = realloc(code, *capacity);
        if (tmp_code == NULL) {
            free(code);
            perror("Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
        code = tmp_code;
    }

    if (strchr("><+-.,[]", c)) {
        code[(*size)++] = c;
        if (c == ',') {
            (*comma_counter)++;
        }
    }

    return code;
}

static char *file_input(const char *filename, size_t *size, size_t *capacity, char *code, int *comma_counter) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        code = add_command(size, capacity, code, (char) c, comma_counter);
    }

    fclose(file);

    return code;
}

static char *add_null_terminator(size_t size, size_t capacity, char *code) {
    if (size >= capacity) {
        capacity += 1;
        char *tmp_code = realloc(code, capacity);
        if (tmp_code == NULL) {
            perror("Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
        code = tmp_code;
    }
    code[size] = '\0';

    return code;
}

char *read_bf_code(const char *filename, int *comma_counter) {
    size_t size = 0;
    size_t capacity = INITIAL_CODE_CAPACITY;

    char *code = malloc(capacity);
    if (code == NULL) {
        perror("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    code = file_input(filename, &size, &capacity, code, comma_counter);

    code = add_null_terminator(size, capacity, code);

    if (size == 0) {
        fprintf(stderr, "Error: No commands found.\n");
        exit(EXIT_FAILURE);
    }

    return code;
}
