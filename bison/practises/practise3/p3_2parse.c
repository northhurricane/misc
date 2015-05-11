#include <stdio.h>
#include <stdlib.h>
#include "p3_2.tab.h"

extern YYSTYPE yylval;

int yylex(YYSTYPE *lvalp)
{
  char buffer[512];
  gets(buffer);
  if (strcmp(buffer, "+") == 0)
  {
    return '+';
  }
  else if (strcmp(buffer, "=") == 0)
  {
    return '=';
  }
  else if (strcmp(buffer, "quit") == 0)
  {
    return TOKEN_QUIT;
  }
  else
  {
    *lvalp = strtod(buffer, NULL);
    return TOKEN_NUMBER;
  }
}

void yyerror(char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
  while (1)
  {
    yyparse();
  }
  return 0;
}
