#include "example1.h"
#include "example1.tab.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
  int r = 0;
  r = yyparse();
  fprintf(stdout, "yyparse return %d\n", r);
  return 0;
}

int input[] = {NUMBER, '+', NUMBER};

static int pos = 0;
int yylex()
{
  int c = input[pos];
  if (pos == 3)
    return 0;
  pos++;
  return c;
}

int yyerror(char * errmsg)
{
  return 0;
}
