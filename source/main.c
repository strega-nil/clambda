#include <clambda/parse_ast.h>

#include <ubclib/format.h>

int main() {
  struct parse_ast ast = parse_ast_make_app(
      parse_ast_make_abs(
          "x",
          parse_ast_make_app(parse_ast_make_var("x"), parse_ast_make_var("x"))),
      parse_ast_make_var("y"));

  print("%\n", parse_ast_format, &ast);

  parse_ast_delete(ast);

  return 0;
}