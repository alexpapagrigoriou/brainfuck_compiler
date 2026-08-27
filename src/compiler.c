#include "compiler.h"
#include <stdio.h>
#include <string.h>

compiler_t compiler_create(char *input_file, char *output_file, compiler_options_t options) {
    compiler_t compiler;

    compiler.options = options;

    snprintf(compiler.input_file, sizeof(compiler.input_file), "%s", input_file);

    if (output_file) {
        snprintf(compiler.output_file, sizeof(compiler.output_file), "%s", output_file);
    } else {
        if (compiler_options_is_enabled(compiler.options, OPT_C_SOURCE_CODE)) {
            const char *base = input_file;
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

            snprintf(compiler.output_file, sizeof(compiler.output_file), "%s.c", base_copy);
        } else {
            snprintf(compiler.output_file, sizeof(compiler.output_file), "a.out");
        }
    }

    return compiler;
}

void compiler_options_enable(compiler_options_t *options, uint8_t opt) {
    *options |= opt;
}

void compiler_options_disable(compiler_options_t *options, uint8_t opt) {
    *options &= ~opt;
}

int compiler_options_is_enabled(compiler_options_t options, uint8_t option) {
    return options & option;
}
