%{
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "p3_1.tab.h"

int yylex (YYSTYPE *lvalp);
void yyerror (char const *);

%}

%token TOK_HELLO TOK_WORLD
%token TOK_WORD

%define api.pure full

%% /* Grammar rules and actions follow.  */

input :
hellow_world {
  printf("hello world!\n");
  return 0;
}
| word {
  printf("word!\n");
  return 0;
}
;

hellow_world : TOK_HELLO TOK_WORLD {
};

word : TOK_WORD {
};



