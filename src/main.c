#include "check.h"
#include "parser.h"
#include "input.h"

int main(int argc, char *argv[]) {
    check_args(argc, argv);

    char *input_file, *output_file;
    parse_input_output_files(argc, argv, &input_file, &output_file);

    // read_bf_code(input_file);

    // check_bf_code();

    // create_output_file();

    return 0;
}
