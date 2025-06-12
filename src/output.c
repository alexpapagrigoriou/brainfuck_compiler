#include "output.h"
#include <stdio.h>
#include <stdlib.h>

void create_output_file(const char *code, int comma_counter, const char *output_file) {
    FILE *file = fopen(output_file, "wx");
    if (file == NULL) {
        perror("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "");

    fclose(file);
}
