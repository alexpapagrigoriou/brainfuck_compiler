#include "output.h"
#include <stdio.h>
#include <stdlib.h>

#define TAB "    "

static int tab_counter = 1;

static void print_tabs(FILE *file) {
    for (int i = 0; i < tab_counter; i++) {
        fprintf(file, TAB);
    }
}

static void greater_than(FILE *file) {
    print_tabs(file);
    fprintf(file, "ptr++;\n");
}

static void less_than(FILE *file) {
    print_tabs(file);
    fprintf(file, "ptr--;\n");
}

static void plus(FILE *file) {
    print_tabs(file);
    fprintf(file, "(*ptr)++;\n");
}

static void minus(FILE *file) {
    print_tabs(file);
    fprintf(file, "(*ptr)--;\n");
}

static void dot(FILE *file) {
    print_tabs(file);
    fprintf(file, "putchar(*ptr);\n");
    fprintf(file, "\n");
}

static void comma(FILE *file) {
    print_tabs(file);
    fprintf(file, "*ptr = next_comma_input();\n");
}

static void open_bracket(FILE *file) {
    fprintf(file, "\n");
    print_tabs(file);
    fprintf(file, "while (*ptr) {\n");

    tab_counter++;
}

static void close_bracket(FILE *file) {
    tab_counter--;

    print_tabs(file);
    fprintf(file, "}\n");
    fprintf(file, "\n");
}

static void generate_command(FILE *file, char c) {
    switch (c) {
        case '>': greater_than(file); break;
        case '<': less_than(file); break;
        case '+': plus(file); break;
        case '-': minus(file); break;
        case '.': dot(file); break;
        case ',': comma(file); break;
        case '[': open_bracket(file); break;
        case ']': close_bracket(file); break;
    }
}

static void generate_bf_source(FILE *file, const char *code) {
    for (size_t i = 0; code[i] != '\0'; i++) {
        generate_command(file, code[i]);
    }
}

static void generate_file(FILE *file, const char *code, int comma_counter) {
    fprintf(file, "#include \"main.h\"\n");
    fprintf(file, "\n");
    fprintf(file, "int main() {\n");
    fprintf(file, TAB "char bf[BF_SIZE] = {0};\n");
    fprintf(file, TAB "char *ptr = bf;\n");
    fprintf(file, "\n");
    fprintf(file, TAB "get_comma_inputs(%d);\n", comma_counter);
    fprintf(file, "\n");

    generate_bf_source(file, code);

    fprintf(file, TAB "putchar('\\n');\n");
    fprintf(file, "\n");
    fprintf(file, TAB "return 0;\n");
    fprintf(file, "}\n");
}

void generate_compiler_file(const char *code, int comma_counter) {
    FILE *file = fopen("compiler_src/main.c", "w");
    if (!file) {
        perror("Error creating file.\n");
        exit(EXIT_FAILURE);
    }

    generate_file(file, code, comma_counter);

    fclose(file);
}
