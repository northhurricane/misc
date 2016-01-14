#ifndef EXAMPLE1_LEX_H_
#define EXAMPLE1_LEX_H_

#include "example1.lex.h"
#include "example1.tab.h"

struct lex_extra_struct
{
  int ival;
};
typedef struct lex_extra_struct lex_extra_t;

void example1_init_lex(yyscan_t *scanner, void *extra, char *str);
void example1_destroy_lex(yyscan_t scanner);
int example1lex(EXAMPLE1STYPE *lvalp, yyscan_t scanner);

#endif//EXAMPLE1_LEX_H_
