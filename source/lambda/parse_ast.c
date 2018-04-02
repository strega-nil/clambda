#include <lambda/parse_ast.h>

#include <stdio.h>
#include <stdlib.h>

void parse_ast_match(
    struct parse_ast const *ast,
    void const *data,
    void (*var)(struct parse_ast_var *, void *),
    void (*abs)(struct parse_ast_abs *, void *),
    void (*app)(struct parse_ast_app *, void *)) {
  switch (ast->tag) {
  case PARSE_AST_VAR:
    var((struct parse_ast_var *)&ast->var, (void *)data);
  case PARSE_AST_ABS:
    abs((struct parse_ast_abs *)&ast->abs, (void *)data);
  case PARSE_AST_APP:
    app((struct parse_ast_app *)&ast->app, (void *)data);
  default:
    abort();
  }
}

static void fprint_var(struct parse_ast_var const *ast, void *file) {
  fprintf(file, "%s", ast->name);
}
static void fprint_abs(struct parse_ast_abs const *ast, void *file) {
  fprintf(file, "(%s.", ast->variable);
  parse_ast_fprint(file, ast->expression);
  fprintf(file, ")");
}
static void fprint_app(struct parse_ast_app const *ast, void *file) {
  parse_ast_fprint(file, ast->callee);
  fprintf(file, " ");
  parse_ast_fprint(file, ast->argument);
}

void parse_ast_fprint(FILE *f, struct parse_ast const *ast) {
  parse_ast_match(ast, f, fprint_var, fprint_abs, fprint_app);
}

void parse_ast_print(struct parse_ast const *ast) {
  parse_ast_fprint(stdout, ast);
}

static struct parse_ast *allocate(struct parse_ast ast) {
  struct parse_ast *ret = calloc(1, sizeof(struct parse_ast));
  *ret = ast;
  return ret;
}

struct parse_ast parse_ast_make_var(char const *name) {
  return (struct parse_ast){
      .tag = PARSE_AST_VAR,
      .var = {.name = name},
  };
}

struct parse_ast parse_ast_make_abs(char const *var, struct parse_ast expr) {
  return (struct parse_ast){
      .tag = PARSE_AST_ABS,
      .abs =
          {
              .variable = var,
              .expression = allocate(expr),
          },
  };
}

struct parse_ast
parse_ast_make_app(struct parse_ast callee, struct parse_ast arg) {
  return (struct parse_ast){
      .tag = PARSE_AST_APP,
      .app =
          {
              .callee = allocate(callee),
              .argument = allocate(arg),
          },
  };
}