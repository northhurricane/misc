%{
#include <stdio.h>

int yylex(int n, char *c);
void yyerror(char *str, int n, char const*);
%}

%lex-param {int n}
%lex-param {char *c}
%parse-param {char *c}
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
  char name[10] = "john";
  while (1)
  {
    yyparse(name, count);
    count++;
    getchar();
  }

  return 0;
}

static int count = 1;
int yylex(int n, char *c)
{
  printf("lex.param is %d.%s\n", n, c);
  count++;
  if ((count % 2) == 0)
    return TOKEN_WORD;

  return 0;
}

void yyerror(char *str, int n, char const* msg)
{
  printf(msg);
}
