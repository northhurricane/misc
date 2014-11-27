/* Infix notation calculator.  */

%{
#include <math.h>
#include <stdio.h>
#include "demo2.lex.h"
void yyerror(yyscan_t scanner, char const *s);
%}

%defines "demo2.tab.h"

%define api.value.type {double}
%define api.pure full

%param {void *scanner}

%token TOKEN_NUMBER

%left '-' '+'
%left '*' '/'
%precedence NEG   /* negation--unary minus */
%right '^'        /* exponentiation */

%%
input:
  %empty
| input line
;

line:
  '\n'
  | exp '\n'  { printf ("\t%.10g\n", $1); }
;
exp:
TOKEN_NUMBER         { $$ = $1;           }
| exp '+' exp        { $$ = $1 + $3;      }
| exp '-' exp        { $$ = $1 - $3;      }
| exp '*' exp        { $$ = $1 * $3;      }
| exp '/' exp        { $$ = $1 / $3;      }
| '-' exp  %prec NEG { $$ = -$2;          }
| exp '^' exp        { $$ = pow ($1, $3); }
| '(' exp ')'        { $$ = $2;           }
;

%%

void
yyerror (yyscan_t scanner, char const *s)
{
  fprintf (stderr, "%s\n", s);
}
