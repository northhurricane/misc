#include "demo2.tab.h"
#include "demo2.lex.h"
#include <stdlib.h>

void main()
{
  while (1)
  {
    char buffer[1024];

    int c;
    int i = 0;
    while ( (c = getchar()) != EOF && c != '\n')
    {
      buffer[i] = c;
      i++;
    }
    buffer[i] = '\n';
    i++;
    buffer[i] = 0;

    yyscan_t scanner;
    yylex_init(&scanner);
    YY_BUFFER_STATE buffer_state = yy_scan_string(buffer, scanner);
    yyparse(scanner);
    yy_delete_buffer(buffer_state, scanner);
    if (c == EOF)
    {
      printf("exit when met ending input\n");
      break;
    }
  }
}
