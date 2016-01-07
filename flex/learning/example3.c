#include <stdio.h>

/*
  example3.l中定义的函数和变量
*/
extern int yylex();
extern int num_lines, num_chars;

int main( int argc, char **argv )
{
  char * str = "123 abc to \ntest string scanner 345\n";
  yy_scan_string (str);

  yylex();

  printf( "# of lines = %d, # of chars = %d\n",
          num_lines, num_chars );
}
