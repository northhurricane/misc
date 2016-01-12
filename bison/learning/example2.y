/*
bison -d  example2.y
gcc example2.c example2.tab.c -o example2
*/

%{
#include "example2.h"
%}

%token NUMBER

%%

input :
/* empty */
| expr
;

expr :
NUMBER '+' NUMBER {
  $$ = $1 + $3;
  fprintf(stdout, "exp result is %d\n", $$);
}
;

%%

