#include <stdio.h>
#include "p4.tab.h"

int yylex(void)
{
  char buffer[512];
  gets(buffer);
  if (strcmp(buffer, "end") == 0)
  {
    return 0;
  }
  else if (strcmp(buffer, "select") == 0)
  {
    return TOKEN_SELECT;
  }
  else if (strcmp(buffer, "delete") == 0)
  {
    return TOKEN_DELETE;
  }
  else if (strcmp(buffer, "table") == 0)
  {
    return TOKEN_TABLE;
  }
  else
  {
    return TOKEN_WORD;
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
    printf("parse exit\n");
  }
}
