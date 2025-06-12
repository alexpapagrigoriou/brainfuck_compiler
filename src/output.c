#include "output.h"
#include <stdio.h>
#include <stdlib.h>

#define TAB "    "

void create_output_file(const char *code, int comma_counter, const char *output_file) {
    FILE *file = fopen("compiler/src/main.c", "w");
    if (file == NULL) {
        perror("Error creating file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "#include \"main.h\"\n");

    fclose(file);
}
