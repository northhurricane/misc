#ifndef _EXAMPLE5_H_
#define _EXAMPLE5_H_

struct example5_extra_struct
{
  int num_lines;
  int num_chars;
};
typedef struct example5_extra_struct example5_extra_t;

void example5_extra_inc_num_lines(void *lex_extra);

void example5_extra_inc_num_chars(void *lex_extra);

#endif//_EXAMPLE5_H_
