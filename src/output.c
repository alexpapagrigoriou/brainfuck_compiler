#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int tab_counter = 1;

static void print_tabs(FILE *file) {
    for (int i = 0; i < tab_counter; i++) {
        fprintf(file, "    ");
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
    fprintf(file, "*ptr = next_comma_input(COMMA_COUNTER);\n");
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
    case '>':
        greater_than(file);
        break;
    case '<':
        less_than(file);
        break;
    case '+':
        plus(file);
        break;
    case '-':
        minus(file);
        break;
    case '.':
        dot(file);
        break;
    case ',':
        comma(file);
        break;
    case '[':
        open_bracket(file);
        break;
    case ']':
        close_bracket(file);
        break;
    }
}

static void generate_bf_source(FILE *file, const char *code) {
    for (size_t i = 0; code[i] != '\0'; i++) {
        generate_command(file, code[i]);
    }
}

static void generate_file(FILE *file, const char *code, size_t comma_counter) {
    fprintf(file, "#include <stddef.h>\n");
    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "#include <stdlib.h>\n");
    fprintf(file, "#include <string.h>\n");
    fprintf(file, "\n");

    fprintf(file, "#define BF_SIZE 30000\n");
    fprintf(file, "#define COMMA_COUNTER %ld\n", comma_counter);
    fprintf(file, "\n");

    fprintf(file, "static char *comma_inputs;\n");
    fprintf(file, "static size_t comma_index = 0;\n");
    fprintf(file, "\n");

    fprintf(file, "void get_comma_inputs(size_t comma_counter) {\n");
    fprintf(file, "    if (comma_counter <= 0) {\n");
    fprintf(file, "        comma_inputs = NULL;\n");
    fprintf(file, "        return;\n");
    fprintf(file, "    }\n");
    fprintf(file, "\n");
    fprintf(file, "    comma_inputs = malloc(comma_counter);\n");
    fprintf(file, "    if (!comma_inputs) {\n");
    fprintf(file, "        perror(\"malloc\");\n");
    fprintf(file, "        exit(EXIT_FAILURE);\n");
    fprintf(file, "    }\n");
    fprintf(file, "\n");
    fprintf(file, "    printf(\"Comma inputs (Provide %%ld character%%s for ',' commands):\\n\", comma_counter, (comma_counter == 1 ? \"\" : \"s\"));\n");
    fprintf(file, "\n");
    fprintf(file, "    size_t comma_index = 0;\n");
    fprintf(file, "    char line[1024];\n");
    fprintf(file, "\n");
    fprintf(file, "    while (comma_index < comma_counter) {\n");
    fprintf(file, "        if (fgets(line, sizeof(line), stdin) == NULL) {\n");
    fprintf(file, "            fprintf(stderr, \"Error reading input.\\n\");\n");
    fprintf(file, "            exit(EXIT_FAILURE);\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        for (size_t i = 0; i < strlen(line) && comma_index < (size_t)comma_counter; i++) {\n");
    fprintf(file, "            if (line[i] != '\\n') {\n");
    fprintf(file, "                comma_inputs[comma_index++] = line[i];\n");
    fprintf(file, "            }\n");
    fprintf(file, "        }\n");
    fprintf(file, "\n");
    fprintf(file, "        if (comma_index < comma_counter) {\n");
    fprintf(file, "            size_t commas_left = comma_counter - comma_index;\n");
    fprintf(file, "            printf(\"\\nComma inputs (Provide %%ld more character%%s for ',' commands):\\n\", commas_left, (commas_left == 1 ? \"\" : \"s\"));\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }\n");
    fprintf(file, "    printf(\"\\n\");\n");
    fprintf(file, "\n");
    fprintf(file, "    printf(\"Output:\\n\");\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");

    fprintf(file, "char next_comma_input(size_t comma_counter) {\n");
    fprintf(file, "    if (comma_index >= comma_counter) {\n");
    fprintf(file, "        fprintf(stderr, \"Runtime error: Comma input not found.\\n\");\n");
    fprintf(file, "        exit(EXIT_FAILURE);\n");
    fprintf(file, "    }\n");
    fprintf(file, "\n");
    fprintf(file, "    return comma_inputs[comma_index++];\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");

    fprintf(file, "void free_comma_inputs(size_t comma_counter) {\n");
    fprintf(file, "    if (comma_counter > 0) {\n");
    fprintf(file, "        free(comma_inputs);\n");
    fprintf(file, "    }\n");
    fprintf(file, "}\n");
    fprintf(file, "\n");

    fprintf(file, "int main() {\n");
    fprintf(file, "    char bf[BF_SIZE] = {0};\n");
    fprintf(file, "    char *ptr = bf;\n");
    fprintf(file, "\n");
    fprintf(file, "    get_comma_inputs(COMMA_COUNTER);\n");
    fprintf(file, "\n");

    generate_bf_source(file, code);

    fprintf(file, "    putchar('\\n');\n");
    fprintf(file, "\n");
    fprintf(file, "    free_comma_inputs(COMMA_COUNTER);\n");
    fprintf(file, "\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
}

static int compile_from_memory(const char *src, size_t len, const char *output_file) {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execlp("gcc", "gcc", "-x", "c", "-", "-o", output_file, (char *)NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }

    close(pipefd[0]);

    size_t written = 0;
    while (written < len) {
        ssize_t result = write(pipefd[1], src + written, len - written);
        if (result < 0) {
            perror("write");
            return -1;
        }

        written += result;
    }

    close(pipefd[1]);

    int status;
    waitpid(pid, &status, 0);

    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

static int generate_c_file(const char *code, size_t comma_counter, const char *output_file) {
    FILE *file = fopen(output_file, "w");
    if (!file) {
        perror("fopen");
        return -1;
    }

    generate_file(file, code, comma_counter);

    fclose(file);

    return 0;
}

static int generate_and_compile_memory_file(const char *code, size_t comma_counter, const char *output_file) {
    char *buffer = NULL;
    size_t buffer_size = 0;

    FILE *mem_file = open_memstream(&buffer, &buffer_size);
    if (!mem_file) {
        perror("mem_file");
        return -1;
    }

    generate_file(mem_file, code, comma_counter);
    fflush(mem_file);

    int result = compile_from_memory(buffer, buffer_size, output_file);

    fclose(mem_file);

    return result;
}

void generate_compiler_file(const char *code, size_t comma_counter, compiler_options_t options, const char *output_file) {
    int result;
    if (compiler_options_is_enabled(options, OPT_C_SOURCE_CODE)) {
        result = generate_c_file(code, comma_counter, output_file);
    } else {
        result = generate_and_compile_memory_file(code, comma_counter, output_file);
    }

    if (result < 0) {
        fprintf(stderr, "Build failed\n");
        exit(EXIT_FAILURE);
    }
}
