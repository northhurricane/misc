#include <stdio.h>
#include "p3_1.tab.h"

/*词法分析接口*/
int yylex(YYSTYPE *lvalp)
{
  char buffer[512];
  gets(buffer);
  if (strcmp(buffer, "hello") == 0)
  {
    return TOK_HELLO;
  }
  else if (strcmp(buffer, "world") == 0)
  {
    return TOK_WORLD;
  }
  else
  {
    return TOK_WORD;
  }
}

/*错误报告接口*/
void
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}


int main(int argc, char *argv[])
{
  while (1)
  {
    yyparse();
  }
}
