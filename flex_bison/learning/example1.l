%option reentrant
%option outfile="example1.lex.c"
%option header-file="example1.lex.h"
%option noyywrap

%{
#include "example1_lex_extra.h"
#include "example1.tab.h"

static int lex_dbg_stop(int id)
{
  return id;
}
%}

DIGIT [0-9]
WHITE [ ]

%%

{DIGIT} {
  example1_lex_extra_set_num(yyextra, yytext[0] - '0');
  return NUMBER;
}

{WHITE} {
  lex_dbg_stop(1);
}

[+] {
  lex_dbg_stop(2);
  return '+';
}

. {
  lex_dbg_stop(3);
  return -1;
}


