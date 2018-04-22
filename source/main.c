#include <clambda/parse_ast.h>

#include <ubclib/format.h>

int
main (void)
{
  struct parse_ast callee = parse_ast_make_app (parse_ast_make_var ("x"),
                                                parse_ast_make_var ("x"));

  struct parse_ast param = parse_ast_make_abs ("x", parse_ast_make_var ("y"));

  struct parse_ast ast = parse_ast_make_app (callee, param);

  print ("%\n", parse_ast_format, &ast);

  parse_ast_delete (ast);

  return 0;
}
