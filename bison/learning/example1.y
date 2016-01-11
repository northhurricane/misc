/*
bison -d  example1.y
gcc example1.c example1.tab.c -o example1
*/

%{
#include "example1.h"
%}

%token NUMBER
%token CHAR
%token OTHER

%%

input :
/* empty */
| expr
| CHAR
| OTHER
;

expr :
NUMBER '+' NUMBER
;

%%
