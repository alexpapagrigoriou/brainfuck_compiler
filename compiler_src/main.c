#include "main.h"

#define COMMAS 0

int main() {
    char bf[BF_SIZE] = {0};
    char *ptr = bf;

    get_comma_inputs(COMMAS);

    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;

    while (*ptr) {
        ptr--;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        ptr++;
        (*ptr)--;
    }

    ptr--;
    putchar(*ptr);

    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;

    while (*ptr) {
        ptr--;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        ptr++;
        (*ptr)--;
    }

    ptr--;
    (*ptr)++;
    putchar(*ptr);

    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    putchar(*ptr);

    putchar(*ptr);

    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    putchar(*ptr);

    ptr++;
    ptr++;
    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;

    while (*ptr) {
        ptr--;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        ptr++;
        (*ptr)--;
    }

    ptr--;
    putchar(*ptr);

    ptr++;
    ptr++;
    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;

    while (*ptr) {
        ptr--;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        ptr++;
        (*ptr)--;
    }

    ptr--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    putchar(*ptr);

    ptr--;
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);

    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    putchar(*ptr);

    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    putchar(*ptr);

    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    (*ptr)--;
    putchar(*ptr);

    ptr++;
    ptr++;
    (*ptr)++;
    putchar(*ptr);

    putchar('\n');

    return 0;
}
