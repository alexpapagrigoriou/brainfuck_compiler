#include "compiler.h"

compiler_t compiler_create(void) {
    compiler_t compiler;

    compiler.input_file[0] = '\0';
    compiler.output_file[0] = '\0';
    compiler.options = 0;

    return compiler;
}

void compiler_options_enable(compiler_options_t *options, uint8_t opt) {
    *options |= opt;
}

void compiler_options_disable(compiler_options_t *options, uint8_t opt) {
    *options &= ~opt;
}

int compiler_options_is_enabled(compiler_options_t options, uint8_t option) {
    return options & option;
}
