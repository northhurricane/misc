#include "example1_lex.h"
#include "example1_parse.h"

/*语法分析的接口*/
int example1_parse(char *str)
{
  yyscan_t scanner;
  lex_extra_t *extra;
  int r;

  example1_init_lex(&scanner, extra, str);
  r = example1parse(scanner);
  example1_destroy_lex(scanner);
  
  return 0;
}

int
example1error(yyscan_t scanner, const char* errmsg)
{
  return 0;
}
