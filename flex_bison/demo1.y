/* Infix notation calculator.  */

%{
#include <math.h>
#include <stdio.h>
#include "demo1.lex.h"

void yyerror (char const *);

%}

%defines "demo1.tab.h"

%define api.value.type {double}

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
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}
