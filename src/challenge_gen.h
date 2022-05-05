#include <stdbool.h>
#include "string.h"
#ifndef __CHAL_GEN__
#define __CHAL_GEN__
typedef enum {
  INT,
  SUM,
  SUM_SYM,
  DIFF,
  DIFF_SYM,
  J_AST_SIZE,
} j_ast_kind;

struct j_ast;

typedef struct {
  struct j_ast **children;
  unsigned int nb_children;
} j_ast_children;

typedef struct j_ast {
  j_ast_children children;
  j_ast_kind kind;
  int value;
} j_ast;

typedef struct {
  string *code;
  int solution;
} j_challenge;

typedef unsigned int *diff_t;

void drop_chal(j_challenge *);
j_challenge *gen_challenge();
string *code_of_node(const j_ast *node, const bool needs_prior);
#endif
