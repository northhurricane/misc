%option outfile="demo3.lex.c"
%option noyywrap

%%
"zap me"

"love" {
  printf("love");
}

.

%%
int main(int argc, char* argv[])
{
  yylex();
}
