/*
例子1：
  演示生成源码后提供的词法分析的接口函数是yylex
生成源码文件：
  flex example1.l
编译
  gcc example1.c example1.lex.c -o example1
*/
%option outfile="example1.lex.c"
%option noyywrap

%{
int num_lines = 0, num_chars = 0;
%}

%%
\n      ++num_lines; ++num_chars;
.       ++num_chars;

