/* scanner for a toy Pascal-like language */
%option outfile="demo2.lex.c"
%option noyywrap
%{
/* need this for the call to atof() below */
#include <math.h>
%}
     
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
     
%%
{DIGIT}+    {
printf( "An integer: %s (%d)\n", yytext,atoi( yytext ) );
}

{DIGIT}+"."{DIGIT}*  {
  printf( "A float: %s (%g)\n", yytext, atof( yytext ) );
}

if|then|begin|end|procedure|function {
  printf( "A keyword: %s\n", yytext );
}

{ID} printf( "An identifier: %s\n", yytext );

"+"|"-"|"*"|"/" {
  printf( "An operator: %s\n", yytext );
}

[ ]+ { 
  printf("space"); 
}

[\t]+ {
  printf("tab meeted"); 
}

[\n]+ {
  printf("new line meeted");
}

%%
int main( int argc, char **argv )
{
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;

  yylex();
}
