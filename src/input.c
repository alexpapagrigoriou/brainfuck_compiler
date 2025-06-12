#include "input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_filename(const char *filename) {
    if (filename[0] == '.' || filename[0] == '-') {
        fprintf(stderr, "Invalid output_file: Filename can't start with '.' or '-'.\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(filename, "bf") == 0) {
        fprintf(stderr, "Invalid output_file: Filename cannot match compiler name ('bf').\n");
        exit(EXIT_FAILURE);
    }

    for (const char *p = filename; *p != '\0'; p++) {
        char c = *p;
        if (!(isalnum((unsigned char)c) || c == '_' || c == '-' || c == '.')) {
            fprintf(stderr, "Invalid output_file: Character '%c' is not allowed.\n", c);
            exit(EXIT_FAILURE);
        }
    }
}

void get_input_output_files(int argc, const char *argv[], const char **input_file, const char **output_file) {
    if (argc == 2) {
        *input_file = argv[1];
        *output_file = "a.out";
        return;
    }

    int input, output;
    if (strcmp(argv[2], "-o") == 0) {
        input = 1;
        output = 3;
    } else {
        input = 3;
        output = 2;
    }

    check_filename(argv[output]);

    *input_file = argv[input];
    *output_file = argv[output];
}
