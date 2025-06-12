#include "input.h"

int main(int argc, char *argv[]) {
    check_args(argc, argv);

    char *input_file, *output_file;
    get_input_output_files(argc, argv, &input_file, &output_file);

    // get_bf_code_from_input_file(input_file);

    // check_if_bf_code_is_valid();

    // create_output_file();

    return 0;
}
