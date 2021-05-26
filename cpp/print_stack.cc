/*
g++ -g -rdynamic print_stack.cc -o print_stack
-rdynamic will return function name
output with -rdynamic
./print_stack(_Z6myfunci+0x1e) [0x400b6e]
output without -rdynamic
./print_stack() [0x40090e]
*/

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <map>
using namespace std;
__thread map<int, int> map1;
void
get_uniq_call_bt(void *bt, int size)
{
  for (int i = 0; i < size; i++)
  {
    
  }
}

void
myfunc3(void)
{
  int j, nptrs;
#define SIZE 100
  void *buffer[100];
  char **strings;

  nptrs = backtrace(buffer, SIZE);
  printf("backtrace() returned %d addresses\n", nptrs);

  /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
     would produce similar output to the following: */

  for (int i = 0; i < nptrs; i++)
  {
    printf("called by %p\n", buffer[i]);
  }

  
  printf("backtrace() returned %d addresses\n", nptrs);
  strings = backtrace_symbols(buffer, nptrs);
  if (strings == NULL) {
    perror("backtrace_symbols");
    exit(EXIT_FAILURE);
  }

  for (j = 0; j < nptrs; j++)
    printf("%s\n", strings[j]);

  free(strings);
}

static void   /* "static" means don't export the symbol... */
myfunc2(void)
{
  myfunc3();
}

void
myfunc(int ncalls)
{
  if (ncalls > 1)
    myfunc(ncalls - 1);
  else
    myfunc2();
}

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "%s num-calls\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  myfunc(atoi(argv[1]));
  exit(EXIT_SUCCESS);
}

