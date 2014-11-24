%option outfile="demo9.lex.c"
%option noyywrap

%{
%}

%%

[0-9]+ printf("digit %s\n", yytext);
[a-zA-Z]+ printf("chars %s\n", yytext);
. printf("unknown char,coding %d\n", yytext[0]);

%%
void main()
{
  char * str = "123 abc to test string scanner 345";
  yy_scan_string (str);
  yylex();
}

