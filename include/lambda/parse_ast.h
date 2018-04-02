#ifndef LAMBDA_PARSE_AST_H
#define LAMBDA_PARSE_AST_H

#include <stdio.h>

enum parse_ast_tag {
  PARSE_AST_VAR,
  PARSE_AST_ABS,
  PARSE_AST_APP,
};

struct parse_ast;

struct parse_ast_var {
  char *name;
};

struct parse_ast_abs {
  char *variable;
  struct parse_ast *expression;
};

struct parse_ast_app {
  struct parse_ast *callee;
  struct parse_ast *argument;
};

struct parse_ast {
  enum parse_expr_tag tag;

  union {
    struct parse_ast_var var;
    struct parse_ast_abs abs;
    struct parse_ast_app app;
  };
};

struct parse_ast parse_ast_make_var(char const *);
struct parse_ast parse_ast_make_abs(char const *, struct parse_ast);
struct parse_ast parse_ast_make_app(struct parse_ast, struct parse_ast);

void parse_ast_delete(struct parse_ast);

void parse_ast_match(
    struct parse_ast const *,
    void const *,
    void (*)(struct parse_ast_var *, void *),
    void (*)(struct parse_ast_abs *, void *),
    void (*)(struct parse_ast_app *, void *));

void parse_ast_format(FILE *, struct parse_ast const *);
void parse_ast_print(struct parse_ast const *);

#endif // LAMBDA_PARSE_AST_H