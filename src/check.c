#include "check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage_message(const char *bf) {
    fprintf(stderr, "Usage 1: %s <input_file>\n", bf);
    fprintf(stderr, "Usage 2: %s <input_file> -o <output_file>\n", bf);
    fprintf(stderr, "Usage 3: %s -o <output_file> <input_file>\n", bf);
}

void check_args(int argc, char *argv[]) {
    if (argc < 2 || argc == 3 || argc > 4) {
        usage_message(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 4 && strcmp(argv[2], "-o") != 0 && strcmp(argv[1], "-o") != 0) {
        usage_message(argv[0]);
        exit(EXIT_FAILURE);
    }
}
