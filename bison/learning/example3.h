#ifndef EXAMPLE3_H_
#define EXAMPLE3_H_

#include <stdio.h>
#include "example3.tab.h"

int yylex(YYSTYPE *lvalp);
int yyerror(char *);

#endif//EXAMPLE3_H_
