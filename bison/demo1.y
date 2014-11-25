/* Reverse polish notation calculator.  */

%{
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int yylex (void);
void yyerror (char const *);

%}

%define api.value.type {float}
%token NUM

%% /* Grammar rules and actions follow.  */

input:
%empty     /* empty */
| input line
             ;

line:     '\n'
| exp '\n'      { printf ("\t%.10g\n", $1); }
;

exp:      NUM           { $$ = $1;           }
| exp exp '+'   {
  printf("exp exp '+' $1:%.10g;$2:%.10g\n", $1, $2);
  $$ = $1 + $2;
}
| exp exp '-'   { 
  printf("exp exp '-' $1:%.10g;$2:%.10g\n", $1, $2);
  $$ = $1 - $2;      
}
| exp exp '*'   { $$ = $1 * $2;      }
| exp exp '/'   { $$ = $1 / $2;      }
/* Exponentiation */
| exp exp '^'   { $$ = pow ($1, $2); }
/* Unary minus    */
| exp 'n'       { $$ = -$1;          }
;

%%

void main()
{
  yyparse();
}

int
yylex (void)
{
  int c;

  /* Skip white space.  */
  while ((c = getchar ()) == ' ' || c == '\t')
    continue;
  /* Process numbers.  */
  if (c == '.' || isdigit (c))
  {
    ungetc (c, stdin);
    scanf ("%lf", &yylval);
    return NUM;
  }
  /* Return end-of-input.  */
  if (c == EOF)
    return 0;
  /* Return a single char.  */
  return c;
}

void
yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}
