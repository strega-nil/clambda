#ifndef UBCLIB_PRINT_H
#define UBCLIB_PRINT_H

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
namespace ubclib {
extern "C" {
#endif

void int_format(FILE *, int const *);
void char_format(FILE *, char const *);
void string_format(FILE *, char const * const *);

void vformat(FILE *, char const *, va_list);
void format(FILE *, char const *, ...);
void print(char const *, ...);

#ifdef __cplusplus
}
} // ub
#endif

#endif // UBCLIB_PRINT_H