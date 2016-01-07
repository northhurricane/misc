#include <stdio.h>

/*
  example4.l中定义的函数和变量
*/
extern int yylex();
extern int num_lines, num_chars;

char * str = "1";
char * str2 = "1\n2";
char * str3 = "1\n2\n3";
int count = 0;

int main( int argc, char **argv )
{
  count = 0;
  yy_scan_string (str);

  yylex();

}

int yywrap (void )
{
  count++;
  printf( "#string %d, # of lines = %d, # of chars = %d\n",
          count, num_lines, num_chars );
  if (count == 1)
  {
    yy_scan_string (str2);
    return 0;
  }
  if (count == 2)
  {
    yy_scan_string (str3);
    return 0;
  }
  if (count == 3)
  {
    return 1;
  }
}
