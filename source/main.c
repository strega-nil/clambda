#include <lambda/parse_ast.h>

#include <stdio.h>

int main() {
  struct parse_ast ast =
      parse_ast_make_app(parse_ast_make_var("f"), parse_ast_make_var("x"));
  parse_ast_print(&ast);
  puts("");

  return 0;
}