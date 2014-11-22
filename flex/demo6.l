%option outfile="demo6.lex.c"
%option noyywrap
%{
%}

%%
foobar    ECHO; yyless(3);
[a-z]+    ECHO;

%%
void main()
{
  yylex();
}
