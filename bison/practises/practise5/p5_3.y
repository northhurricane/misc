%{
#include <stdio.h>

int yylex(int n);
void yyerror(int n, char const*);
%}

%lex-param {int n}
%parse-param {int n}

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
    yyparse(count);
    count++;
    getchar();
  }

  return 0;
}

static int count = 1;
int yylex(int n)
{
  printf("lex.param is %d.\n", n);
  count++;
  if ((count % 2) == 0)
    return TOKEN_WORD;

  return 0;
}

void yyerror(int n, char const* msg)
{
  printf(msg);
}
