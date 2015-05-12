%{
#include <stdio.h>

int yylex(void);
void yyerror(char const *);
%}

%token TOKEN_DELETE TOKEN_SELECT
%token TOKEN_TABLE
%token TOKEN_WORD

%%

input :
TOKEN_WORD {
  printf("word\n");
}
|
TOKEN_SELECT {
  printf("select\n");
}
|
delete_table delete_table {
  printf("delete table\n");
};

delete_table :
TOKEN_DELETE TOKEN_TABLE {
  printf("delete table\n");
};

delete_table :
TOKEN_WORD {};


