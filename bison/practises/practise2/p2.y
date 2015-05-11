%{
#include <stdio.h>
int yylex(void);
void yyerror(char const *);
%}

%token TOKEN_NUMBER
%token TOKEN_QUIT

%define api.value.type {double}

%%

input :
expr '=' {
  printf("result is %f\n", $1);
  return 0;
}
| TOKEN_QUIT {
  printf("quit\n");
  return 0;
};

expr :
expr '+' TOKEN_NUMBER {
  $$ = $1 + $3;
  //printf("expr rule 1 $1 is %f, $2 is %f\n", $1, $3);
}
| TOKEN_NUMBER {
  $$ = $1;
}

