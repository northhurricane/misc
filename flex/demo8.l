%option outfile="demo8.lex.c"
%option noyywrap

%{
int comment_line_number = 0;
%}

%x comment

%%

"/*" {
  comment_line_number = 0;
  printf("=============comment begin=============\n");
  BEGIN(comment);
}

<comment>[^*\n]* printf("%s", yytext);
<comment>"*"+[^*/\n]* printf("%s", yytext);
<comment>\n printf("%s", yytext);comment_line_number++;
<comment>"*"+"/" {
  printf("comment line is %d \n", comment_line_number);
  printf("=============comment end=============\n");
  BEGIN(INITIAL);
}

. ECHO;

%%
void main()
{
  yylex();
}
