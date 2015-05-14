%{
#include <stdio.h>

int yylex(int n);
void yyerror(char const*);
%}

%lex-param {int n}

%token TOKEN_WORD

%%

input :
TOKEN_WORD {
}

%%
int main(int argc, char *argv[])
{
  int count = 0;
  while (1)
  {
    yyparse();
  }

  return 0;
}

int yylex(int n)
{
  if ((n % 2) == 0)
    return TOKEN_WORD;
  return 0;
}

void yyerror(char const* msg)
{
  printf(msg);
}

