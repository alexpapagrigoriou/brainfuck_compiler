int main(int argc, char *argv[]) {
    check_args(argc, argv);

    char *input_file, *output_file;
    find_input_output_files(argc, argv, input_file, output_file);

    open_input_file(input_file);

    check_if_input_is_valid();

    create_output_file();

    return 0;
}
