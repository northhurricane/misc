%{
#include <stdlib.h>
#include "demo2.tab.h"  //generated from demo1.y by bison
%}

%option outfile="demo2.lex.c" HEADER-FILE="demo2.lex.h"
%option noyywrap
%option reentrant
%option bison-bridge

white [\t ]
digit [0-9]
integer {digit}+
decimal (({digit}*\.{digit}+)|({digit}+\.{digit}*))

%%

{integer} {
  char istr[128];
  strncpy(istr, yytext, yyleng);
  *yylval_param = (YYSTYPE)atoi(istr);
  return TOKEN_NUMBER;
}

{decimal} {
  char dstr[128];
  strncpy(dstr, yytext, yyleng);
  *yylval_param = (YYSTYPE)atof(dstr);
  return TOKEN_NUMBER;
}

{white}

\n { return yytext[0]; }

. { return yytext[0]; }

%%


