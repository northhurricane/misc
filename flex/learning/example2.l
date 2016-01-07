/*
例子2：
  演示yyin的使用
生成源码文件：
  flex example2.l
编译
  gcc example2.c example2.lex.c -o example2
*/
%option outfile="example2.lex.c"
%option noyywrap

%{
int num_lines = 0, num_chars = 0;
%}

%%
\n      ++num_lines; ++num_chars;
.       ++num_chars;
