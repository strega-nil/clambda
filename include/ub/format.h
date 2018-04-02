#ifndef UB_PRINT_H
#define UB_PRINT_H

#include <stdarg.h>
#include <stdio.h>

void int_format(FILE *, int const *);
void char_format(FILE *, char const *);
void string_format(FILE *, char const * const *);

void vformat(FILE *, char const *, va_list);
void format(FILE *, char const *, ...);
void print(char const *, ...);

#endif