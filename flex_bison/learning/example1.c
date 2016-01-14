/*
例子5：
  演示
生成源码文件：
  flex example1.l
  bison -d example1.y
编译
  gcc example1.c example1.lex.c example1_lex.c example1_parse.c example1.tab.c -o example1
*/


#include "example1_parse.h"

int main( int argc, char **argv )
{
  int r;
  char * str = "1 + 2";
  r = example1_parse(str);
}


