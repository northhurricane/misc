#include <stdio.h>

typedef int (*printi_t)(int i);

int my_printi(int i)
{
  printf("my_printi:%d\n", i);
}

int his_printi(int i)
{
  printf("his_printi:%d\n", i);
}

void her_printi(int i)
{
  printf("her_printi:%d\n", i);
}

int
main(int argc, char *argv[])
{
  printi_t printit = my_printi;
  printit(1);
  printit = his_printi;
  printit(1);
  //导致警告
  //printit = her_printi;
  //printit(1);
}
