/*
bison -d  example3.y
gcc example3.c example3.tab.c -o example3
*/

%{
#include "example3.h"
%}

%define api.pure full

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

