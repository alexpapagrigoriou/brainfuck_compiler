#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>

#define MAX_FILE_NAME_LENGTH 256

#define OPT_C_SOURCE_CODE (UINT8_C(1) << 0)

typedef uint8_t compiler_options_t;

typedef struct {
    char input_file[MAX_FILE_NAME_LENGTH];
    char output_file[MAX_FILE_NAME_LENGTH];
    compiler_options_t options;
} compiler_t;

compiler_t compiler_create(void);

void compiler_options_enable(compiler_options_t *options, uint8_t opt);
void compiler_options_disable(compiler_options_t *options, uint8_t opt);
int compiler_options_is_enabled(compiler_options_t options, uint8_t option);

#endif
