/*
例子5：
  演示
生成源码文件：
  flex example5.l
编译
  gcc example5.c example5.lex.c -o example5
*/
%option reentrant
%option outfile="example5.lex.c"
%option header-file="example5.lex.h"
%option noyywrap

%{
#include "example5.h"
%}

%%
\n      example5_extra_inc_num_lines(yyextra);
.       example5_extra_inc_num_chars(yyextra);
