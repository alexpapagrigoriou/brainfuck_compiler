#include "args.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage_message(const char *bf) {
    printf("Usage: %s [options] file...\n", bf);
    printf("Options:\n");
    printf("  --help     Display this information.\n");
    printf("  -c         Genereate the C source code.\n");
    printf("  -o <file>  Place the output into <file>.\n");
}

static void check_filename(const char *filename) {
    if (filename[0] == '.' || filename[0] == '-') {
        fprintf(stderr, "Invalid output_file: Filename can't start with '.' or '-'.\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(filename, "bf") == 0) {
        fprintf(stderr, "Invalid output_file: Filename cannot match compiler name 'bf'.\n");
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

compiler_t check_args(int argc, char *argv[]) {
    int input = -1, output = -1;
    compiler_options_t options = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            usage_message(argv[0]);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "-c") == 0) {
            compiler_options_enable(&options, OPT_C_SOURCE_CODE);
        } else if (strcmp(argv[i], "-o") == 0) {
            i++;
            if (i >= argc) {
                fprintf(stderr, "Missing output file.\n");
                exit(EXIT_FAILURE);
            }

            output = i;
            check_filename(argv[output]);
        } else {
            if (input == -1) {
                input = i;
            } else {
                usage_message(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    if (input == -1) {
        usage_message(argv[0]);
        exit(EXIT_FAILURE);
    }

    return compiler_create(argv[input], output == -1 ? NULL : argv[output], options);
}
