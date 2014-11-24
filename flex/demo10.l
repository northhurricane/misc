%option reentrant
%option outfile="demo10.lex.c"
%option noyywrap

%x COMMENT

%%
"//" BEGIN(COMMENT);
.|\n 

<COMMENT>\n          BEGIN(INITIAL);
<COMMENT>[^\n]+      fprintf( yyout, "%s\n", yytext);

%%
int main ( int argc, char * argv[] )
{
  yyscan_t scanner;
     
  yylex_init ( &scanner );
  yylex ( scanner );
  yylex_destroy ( scanner );
  return 0;
}