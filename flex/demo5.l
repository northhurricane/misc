%option outfile="demo5.lex.c"
%option noyywrap

%{
int word_count = 0;
void special()
{
}
%}

%%

frob        special(); REJECT;
[^ \t\n]+   {
  ++word_count;
  printf("words : %d\n", word_count);
}

%%
void main()
{
  yylex();
}
