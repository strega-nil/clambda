#include <lambda/parse_ast.h>

#include <ub/format.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_ast_match(
    struct parse_ast const *ast,
    void const *data,
    void (*var)(struct parse_ast_var *, void *),
    void (*abs)(struct parse_ast_abs *, void *),
    void (*app)(struct parse_ast_app *, void *)) {
  switch (ast->tag) {
  case PARSE_AST_VAR:
    var((struct parse_ast_var *)&ast->var, (void *)data);
    break;
  case PARSE_AST_ABS:
    abs((struct parse_ast_abs *)&ast->abs, (void *)data);
    break;
  case PARSE_AST_APP:
    app((struct parse_ast_app *)&ast->app, (void *)data);
    break;
  default:
    abort();
  }
}

static void format_var(struct parse_ast_var const *ast, void *file) {
  fputs(ast->name, file);
}
static void format_abs(struct parse_ast_abs const *ast, void *file) {
  format(
      file,
      "(%.%)",
      string_format,
      &ast->variable,
      parse_ast_format,
      ast->expression);
}
static void format_app(struct parse_ast_app const *ast, void *file) {
  format(
      file,
      "% %",
      parse_ast_format,
      ast->callee,
      parse_ast_format,
      ast->argument);
}

void parse_ast_format(FILE *f, struct parse_ast const *ast) {
  parse_ast_match(ast, f, format_var, format_abs, format_app);
}

void parse_ast_print(struct parse_ast const *ast) {
  parse_ast_format(stdout, ast);
}

static struct parse_ast *allocate(struct parse_ast ast) {
  struct parse_ast *ret = calloc(1, sizeof(struct parse_ast));
  *ret = ast;
  return ret;
}

static char *allocate_str(char const *old) {
  size_t const length = strlen(old);
  char *new_ = calloc(length + 1, 1);
  memcpy(new_, old, length);
  return new_;
}

struct parse_ast parse_ast_make_var(char const *name) {
  struct parse_ast ret;
  struct parse_ast_var var;

  var.name = allocate_str(name);

  ret.tag = PARSE_AST_VAR;
  ret.var = var;

  return ret;
}

struct parse_ast parse_ast_make_abs(char const *var, struct parse_ast expr) {
  struct parse_ast ret;
  struct parse_ast_abs abs;

  abs.variable = allocate_str(var);
  abs.expression = allocate(expr);

  ret.tag = PARSE_AST_ABS;
  ret.abs = abs;

  return ret;
}

struct parse_ast
parse_ast_make_app(struct parse_ast callee, struct parse_ast arg) {
  struct parse_ast ret;
  struct parse_ast_app app;

  app.callee = allocate(callee);
  app.argument = allocate(arg);

  ret.tag = PARSE_AST_APP;
  ret.app = app;

  return ret;
}

static void delete_var(struct parse_ast_var *ast, void *ignore) {
  (void)ignore;
  free(ast->name);
}
static void delete_abs(struct parse_ast_abs *ast, void *ignore) {
  (void)ignore;
  free(ast->variable);
  parse_ast_delete(*ast->expression);
  free(ast->expression);
}
static void delete_app(struct parse_ast_app *ast, void *ignore) {
  (void)ignore;
  parse_ast_delete(*ast->callee);
  free(ast->callee);
  parse_ast_delete(*ast->argument);
  free(ast->argument);
}

void parse_ast_delete(struct parse_ast ast) {
  parse_ast_match(&ast, NULL, delete_var, delete_abs, delete_app);
}