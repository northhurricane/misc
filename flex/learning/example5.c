#include <stdio.h>
#include "example5.lex.h"
#include "example5.h"

int main( int argc, char **argv )
{
  char * str = "1\n2\n";
  yyscan_t scanner;
  example5_extra_t extra;

  yylex_init(&scanner);
  yyset_extra(&extra, scanner);
  yy_scan_string(str, scanner);
  yylex(scanner);
  yylex_destroy(scanner);

  printf( "# of lines = %d, # of chars = %d\n",
          extra.num_lines, extra.num_chars );
}

inline void example5_extra_inc_num_lines(void *lex_extra)
{
  example5_extra_t *extra = (example5_extra_t *)lex_extra;
  extra->num_lines++;
}

inline void example5_extra_inc_num_chars(void *lex_extra)
{
  example5_extra_t *extra = (example5_extra_t *)lex_extra;
  extra->num_chars++;;
}

