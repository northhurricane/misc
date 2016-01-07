/*
例子3：
  演示字符串的词法分析
生成源码文件：
  flex example3.l
编译
  gcc example3.c example3.lex.c -o example3
*/
%option outfile="example3.lex.c"
%option noyywrap

%{
int num_lines = 0, num_chars = 0;
%}

%%
\n      ++num_lines; ++num_chars;
.       ++num_chars;
