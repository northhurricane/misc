#include <stdio.h>

/*
  example1.l中定义的函数和变量
*/
extern int yylex();
extern int num_lines, num_chars;
/*windows使用Ctrl+Z结束输入，linux使用Ctrl+D结束输入*/
int main(int argc, char *argv[])
{
  yylex();
  printf( "# of lines = %d, # of chars = %d\n",
          num_lines, num_chars );
  return 0;
}
