%option outfile="demo7.lex.c"
%option noyywrap

%{
#include <math.h>
%}

%s expect

%%
expect-floats BEGIN(expect);

<expect>[0-9]+.[0-9]+ {
  printf("found a float %f\n", atof(yytext));
}

<expect>end-expect BEGIN(INITIAL);

[0-9]+ printf("found digit %s\n", yytext);

"." printf("found dot\n");

%%
void main()
{
  yylex();
}
