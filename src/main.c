#include "args.h"
#include "check.h"
#include "parser.h"
#include "input.h"
#include "output.h"

int main(int argc, char *argv[]) {
    check_args(argc, argv);

    char *input_file, *output_file;
    parse_input_output_files(argc, argv, &input_file, &output_file);

    int comma_counter = 0;
    char *code = read_bf_code(input_file, &comma_counter);

    check_bf_code(code);

    create_output_file(code, comma_counter);

    return 0;
}
