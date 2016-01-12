#include "example2.h"
#include "example2.tab.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  int r = 0;
  r = yyparse();
  fprintf(stdout, "yyparse return %d\n", r);
  return 0;
}

int input[] = {NUMBER, '+', NUMBER};
int vals[] = {1, 2};

static int pos = 0;
int yylex()
{
  int c;
  switch (pos)
  {
  case 0:
    yylval = vals[0];
    break;
  case 1:
    break;
  case 2:
    yylval = vals[1];
    break;
  default:
    return 0;
  }
  c = input[pos];
  pos++;
  return c;
}

int yyerror(char * errmsg)
{
  return 0;
}
