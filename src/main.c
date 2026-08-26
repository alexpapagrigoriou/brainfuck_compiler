#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "check.h"
#include "compiler.h"
#include "input.h"
#include "output.h"

int main(int argc, char *argv[]) {
    compiler_t compiler = compiler_create();

    check_args(argc, argv, &compiler);
    printf("Input file main: %s\n", compiler.input_file);
    printf("Output file main: %s\n", compiler.output_file);

    size_t comma_counter = 0;
    char *code = read_bf_code(compiler.input_file, &comma_counter);

    check_bf_code(code);

    generate_compiler_file(code, comma_counter, compiler.options, compiler.output_file);

    free(code);

    return 0;
}
