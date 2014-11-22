%option outfile="demo4.lex.c"
%option noyywrap

%{
%}

%%

mega-    {
  printf("yytext:%s yylen:%d", yytext, yyleng);
  ECHO; yymore();
}
kludge   {
  printf("yytext:%s yylen:%d", yytext, yyleng);
  ECHO;
}

%%
void main()
{
  yylex();
}
