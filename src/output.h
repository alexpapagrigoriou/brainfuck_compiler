#ifndef OUTPUT_H
#define OUTPUT_H

#include <stddef.h>

#include "compiler.h"

void generate_compiler_file(const char *code, size_t comma_counter, compiler_options_t options, const char *output_file);

#endif
