%{
#include <stdio.h>
%}

%option outfile="number.lex.c"
%option noyywrap

digit [0-9]
integer {digit}+
decimal {digit}*\.{digit}+|{digit}+\.{digit}*
scientific_notation {decimal}[eE][+-]?{integer}

%%

{integer} printf("integer:%s\n", yytext);
{decimal} printf("decimal:%s\n", yytext);
{scientific_notation} printf("scientific notation:%s\n", yytext);

%%

void main()
{
  yylex();
}
