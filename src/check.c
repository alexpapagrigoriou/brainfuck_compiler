#include "check.h"
#include <stdio.h>
#include <stdlib.h>

#define BF_SIZE 30000
#define BRACKET_MAX 100

void greater_than(size_t *index) {
    if (*index >= BF_SIZE - 1) {
        fprintf(stderr, "\nCompilation error: Range error.\n");
        exit(EXIT_FAILURE);
    }

    (*index)++;
}

void less_than(size_t *index) {
    if (*index <= 0) {
        fprintf(stderr, "\nCompilation error: Range error.\n");
        exit(EXIT_FAILURE);
    }

    (*index)--;
}

void open_bracket(int *brackets) {
    if (*brackets >= BRACKET_MAX - 1) {
        fprintf(stderr, "\nCompilation error: Bracket stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    (*brackets)++;
}

void close_bracket(int *brackets) {
    if (*brackets <= 0) {
        fprintf(stderr, "\nCompilation error: Unbalanced brackets.\n");
        exit(EXIT_FAILURE);
    }

    (*brackets)--;
}

void check_command(char c, int *brackets) {
    static size_t index = 0;

    switch (c) {
        case '>': greater_than(&index); break;
        case '<': less_than(&index); break;
        case '[': open_bracket(brackets); break;
        case ']': close_bracket(brackets); break;
    }
}

void check_bf_code(char *code) {
    int brackets = 0;

    for (size_t i = 0; code[i] != '\0'; i++) {
        check_command(code[i], &brackets);
    }

    if (brackets != 0) {
        fprintf(stderr, "\nCompilation error: Unbalanced brackets - %d unmatched '['.\n", brackets);
        exit(EXIT_FAILURE);
    }
}
