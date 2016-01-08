/*
例子6：
  演示条件词法分析
生成源码文件：
  flex example6.l
编译
  gcc example6.lex.c -o example6
*/
%option outfile="example6.lex.c"
%option noyywrap

%{
#include <math.h>
int comment_num_chars = 0;
int none_comment_num_chars = 0;
%}

%s COMMENT

%%
"/*" BEGIN(COMMENT);
<COMMENT>"*/" BEGIN(INITIAL);
<COMMENT>. comment_num_chars++;
. none_comment_num_chars++;

%%
void main()
{
  yylex();
  printf( "# of coment chars = %d, # of none comment chars = %d\n",
          comment_num_chars, none_comment_num_chars );
}
