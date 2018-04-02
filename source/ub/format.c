#include <ub/format.h>

#include <stdarg.h>
#include <stddef.h>

typedef void format_t(FILE *, void const *);

void int_format(FILE *f, int const *data) { fprintf(f, "%d", *data); }
void char_format(FILE *f, char const *data) { fputc(*data, f); }
void string_format(FILE *f, char const *const *data) { fputs(*data, f); }

void vformat(FILE *f, char const *fmt, va_list args) {
  for (; *fmt != '\0'; ++fmt) {
    if (*fmt == '%') {
      format_t *func = va_arg(args, format_t *);
      void const *data = va_arg(args, void const *);
      func(f, data);
    } else {
      fputc(*fmt, f);
    }
  }
}

void format(FILE *f, char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  vformat(f, fmt, args);

  va_end(args);
}

void print(char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  vformat(stdout, fmt, args);

  va_end(args);
}