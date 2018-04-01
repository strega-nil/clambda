#ifndef UB_PARSE_AST_H
#define UB_PARSE_AST_H

enum parse_expr_tag {
  PARSE_EXPR_FOO
};

struct parse_expr {
  enum parse_expr_tag tag;
};

#endif // UB_PARSE_AST_H