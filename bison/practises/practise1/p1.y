%{
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int yylex (void);
void yyerror (char const *);

%}

%token TOK_HELLO TOK_WORLD
%token TOK_WORD

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



