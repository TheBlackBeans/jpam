#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "challenge_gen.h"
#include "string.h"

#define TARGET_DIFFICULTY 50
#define VALUE_RANGE 20

unsigned int nb_children(const j_ast_kind kind) {
  switch (kind) {
  case INT:
    return 0;
  case SUM:
  case DIFF:
  case SUM_SYM:
  case DIFF_SYM:
    return 2;
  default:
    exit(EXIT_FAILURE);
  }
}

unsigned int compute_difficulty(const j_ast_kind kind) {
  switch (kind) {
  case INT:
    return 0;
  case SUM:
  case DIFF:
  case SUM_SYM:
  case DIFF_SYM:
    return 10;
  default:
    exit(EXIT_FAILURE);
  }
}

void compute_value(j_ast *node) {
  for (int i = 0; i < node->children.nb_children; i++) {
    compute_value(*(node->children.children+i));
  }
  switch (node->kind) {
  case INT:
    node->value = rand() % VALUE_RANGE;
    break;
  case SUM:
  case SUM_SYM:
    node->value = (*node->children.children)->value + (*(node->children.children+1))->value;
    break;
  case DIFF:
  case DIFF_SYM:
    node->value = (*node->children.children)->value - (*(node->children.children+1))->value;
    break;
  default:
    exit(EXIT_FAILURE);
  }
}

void code_for_dyadic(const j_ast_children *children,
		     const string *symbol,
		     const bool needs_prior,
		     string *code) {
  string *buffer;
  *code = *new_string();
  if (needs_prior)
    string_push(code, '(');
  buffer = code_of_node(*children->children, true);
  extend_string(code, buffer);
  extend_string(code, symbol);
  drop(buffer);
  buffer = code_of_node(*(children->children+1), false);
  extend_string(code, buffer);
  drop(buffer);
  if (needs_prior)
    string_push(code, ')');
}

string *code_of_node(const j_ast *node, const bool needs_prior) {
  string *code = null_string();
  string *symbol;
  switch (node->kind) {
  case INT:
    code = of_int(node->value);
    break;
  case SUM:
    symbol = of_str("+");
    code_for_dyadic(&node->children, symbol, needs_prior, code);
    drop(symbol);
    break;
  case SUM_SYM:
    symbol = of_str("+~");
    code_for_dyadic(&node->children, symbol, needs_prior, code);
    drop(symbol);
    break;
  case DIFF:
    symbol = of_str("-");
    code_for_dyadic(&node->children, symbol, needs_prior, code);
    drop(symbol);
    break;
  case DIFF_SYM:
    symbol = of_str("-~");
    code_for_dyadic(&node->children, symbol, needs_prior, code);
    drop(symbol);
    break;
  default:
    exit(EXIT_FAILURE);
  }
  return code;
}

void drop_chal(j_challenge *chal) {
  drop(chal->code);
  free(chal);
}

j_ast *gen_node(diff_t difficulty) {
  j_ast *node = malloc(sizeof(j_ast));;
  if (*difficulty > TARGET_DIFFICULTY) {
    node->children.children = NULL;
    node->children.nb_children = 0;
    node->kind = INT;
  } else {
    node->kind = rand() % J_AST_SIZE;
    *difficulty += compute_difficulty(node->kind);
    node->children.nb_children = nb_children(node->kind);
    node->children.children = malloc(sizeof(void *)*node->children.nb_children);
    for (int i = 0; i < node->children.nb_children; i++) {
      *(node->children.children+i) = gen_node(difficulty);
    }
  }
  compute_value(node);
  return node;
}

void drop_ast(j_ast *node) {
  for (int i = 0; i < node->children.nb_children; i++) {
    drop_ast(*(node->children.children+i));
  }
  free(node);
}

j_challenge *gen_challenge() {
  diff_t difficulty = malloc(sizeof(unsigned int));
  *difficulty = 0;

  srand(time(NULL));

  j_ast *root = gen_node(difficulty);
  j_challenge *result = malloc(sizeof(j_challenge));
  result->solution = root->value;
  result->code = code_of_node(root, false);
  drop_ast(root);
  return result;
}
