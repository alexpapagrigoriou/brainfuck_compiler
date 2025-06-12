#include "output.h"
#include <stdio.h>
#include <stdlib.h>

void create_output_file(const char *code, int comma_counter, const char *output_file) {
    FILE *file = fopen("../compiler/src/main.c", "w");
    if (file == NULL) {
        perror("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "#include \"comma_input.h\"\n");
    fprintf(file, "#include <stdio.h>\n");

    fclose(file);
}
