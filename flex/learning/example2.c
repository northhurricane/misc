#include <stdio.h>

/*
  example2.l中定义的函数和变量
*/
extern int yylex();
extern int num_lines, num_chars;
extern FILE *yyin;
/*执行程序的参数不指定输入文件，windows使用Ctrl+Z结束输入，linux使用Ctrl+D结束输入*/
int main( int argc, char **argv )
{
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;

  yylex();

  printf( "# of lines = %d, # of chars = %d\n",
          num_lines, num_chars );
}

