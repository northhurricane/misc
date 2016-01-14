%{
#include <stdio.h>
%}

%define api.pure full
%param {void *scanner}
%define api.prefix {example1}

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
