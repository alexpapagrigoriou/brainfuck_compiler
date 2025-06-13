#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

void compile_generated_file(const char *output_file) {
    const char *template = "make --no-print-directory -C compiler_src TARGET_NAME=%s";
    size_t len = snprintf(NULL, 0, template, output_file) + 1;

    char *command = malloc(len);
    if (!command) {
        perror("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    snprintf(command, len, template, output_file);

    int status = system(command);

    free(command);

    if (status == -1) {
        perror("Compilation error.\n");
    } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        fprintf(stderr, "Error: gcc compilation failed with exit code %d.\n", WEXITSTATUS(status));
        exit(EXIT_FAILURE);
    }
}
