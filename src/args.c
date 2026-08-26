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

void check_args(int argc, char *argv[], compiler_t *compiler) {
    int input = -1, output = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            usage_message(argv[0]);
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "-c") == 0) {
            compiler_options_enable(&compiler->options, OPT_C_SOURCE_CODE);
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

    snprintf(compiler->input_file, sizeof(compiler->input_file), "%s", argv[input]);

    if (output != -1) {
        snprintf(compiler->output_file, sizeof(compiler->output_file), "%s", argv[output]);
    } else {
        if (compiler_options_is_enabled(compiler->options, OPT_C_SOURCE_CODE)) {
            const char *base = argv[input];
            const char *slash = strrchr(base, '/');
            if (slash != NULL) {
                base = slash + 1;
            }

            char base_copy[MAX_FILE_NAME_LENGTH - 2];
            snprintf(base_copy, sizeof(base_copy), "%s", base);
            char *dot = strrchr(base_copy, '.');
            if (dot != NULL) {
                *dot = '\0';
            }

            snprintf(compiler->output_file, sizeof(compiler->output_file), "%s.c", base_copy);
        } else {
            snprintf(compiler->output_file, sizeof(compiler->output_file), "a.out");
        }
    }
}
