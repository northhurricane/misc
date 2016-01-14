#include "example1_lex.h"
#include "example1_lex_extra.h"

void example1_init_lex(yyscan_t *scanner, void *extra, char *str)
{
  int r = 0;
  r = yylex_init(scanner);
  yyset_extra(extra, *scanner);
  yy_scan_string(str, *scanner);
}

void example1_destroy_lex(yyscan_t scanner)
{
  yylex_destroy(scanner);
}

void example1_lex_extra_set_num(void *extra, int num)
{
  ((lex_extra_t*)extra)->ival = num;
}

/*为yyparse提供的接口*/
int example1lex(EXAMPLE1STYPE *lvalp, yyscan_t scanner)
{
  int r;
  lex_extra_t *extra;

  r = yylex(scanner);
  extra = (lex_extra_t*)yyget_extra(scanner);
  *lvalp = extra->ival;

  return r;
}

/*
//test
//gcc example1_lex.c example1.lex.c -o example1 -g 
int main(int argc, char *argv[])
{
  yyscan_t scanner;
  lex_extra_t extra;
  char *str = "1 + 2";
  int r = 0;

  example1_init_lex(&scanner, &extra, str);
  do {
    r = yylex(scanner);
  } while (r > 0);  
  example1_destroy_lex(scanner);
  return 0;
}
//*/
