/*
例子4：
  演示yywrap的用法
生成源码文件：
  flex example4.l
编译
  gcc example4.c example4.lex.c -o example4
*/
%option outfile="example4.lex.c"

%{
int num_lines = 0, num_chars = 0;
%}

%%
\n      ++num_lines; ++num_chars;
.       ++num_chars;
