#include <stddef.h>
#include "args.h"
#include "check.h"
#include "parser.h"
#include "input.h"
#include "output.h"
#include "compiler.h"

int main(int argc, char *argv[]) {
    check_args(argc, argv);

    char *input_file, *output_file;
    parse_input_output_files(argc, argv, &input_file, &output_file);

    size_t comma_counter = 0;
    char *code = read_bf_code(input_file, &comma_counter);

    check_bf_code(code);

    generate_compiler_file(code, comma_counter);

    compile_generated_file(output_file);

    return 0;
}
