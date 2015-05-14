%{
#include <stdio.h>

int yylex();
void yyerror(int n, char const*);
%}

%parse-param {int n}

%token TOKEN_WORD

%%

input :
TOKEN_WORD {
  printf("count is %d.\n", n);
}

%%
int main(int argc, char *argv[])
{
  int count = 0;
  while (1)
  {
    yyparse(count);
    printf("parse count %d.\n", count);
    count++;
    getchar();
  }

  return 0;
}

static int lex_count = 1;
int yylex()
{
  lex_count++;
  if ((lex_count % 2) == 0)
    return TOKEN_WORD;
  return 0;
}

void yyerror(int n, char const* msg)
{
  printf(msg);
}

