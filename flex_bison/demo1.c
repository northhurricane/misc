#include "demo1.lex.h"
#include "demo1.tab.h"
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

    YY_BUFFER_STATE buffer_state = yy_scan_string(buffer);
    yyparse();
    yy_delete_buffer(buffer_state);
    if (c == EOF)
    {
      printf("exit when met ending input\n");
      break;
    }
  }
}
