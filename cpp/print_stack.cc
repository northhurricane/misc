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
#include <string.h>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
#define SIZE 64

//用来存储堆栈二进制的结构，假设最多只存储SIZE大小的堆栈，第一个字节用来存储
//调用堆栈的层数
typedef char addr_bin_t[sizeof(void*) * SIZE + 1];

/*
  将数据还原为数组模式
*/
void
print_reorg_bt(char *bt)
{
  int nptrs = bt[0];
  void *ptrs[SIZE];
  char *addr = bt + 1;
  assert(nptrs <= SIZE); 
  for (int i = 0; i < nptrs && i < SIZE; i++)
  {
    memcpy(&ptrs[i], addr, sizeof(void*));
    addr += sizeof(void*);
  }

  char **strings;
  strings = backtrace_symbols(ptrs, nptrs);
  if (strings == NULL) {
    perror("backtrace_symbols");
    exit(EXIT_FAILURE);
  }
  free(strings);
}
/*
  重新组织backtrace的内容，假设堆栈的深度不超过100，将堆栈深度和每个堆栈
  地址进行拼接。基于此方法，可以在对堆栈进行唯一性的生成，从而对相同堆栈
  进行判断。
*/
void
reorg_call_bt(void *bt[], int size_, char *buff)
{
  void *current_ptr = NULL;
  char *addrs = buff;
  int size = size_ > SIZE ? SIZE : size;
  addrs[0] = (char)size;
  char *curr_addr = addrs + 1;
  for (int i = 0; i < size; i++)
  {
    memcpy(curr_addr, bt + i, sizeof(void*));
    curr_addr += sizeof(void*);
  }
  int len = curr_addr - addrs;
  printf("backtrace() reorg addresses length %d\n", len);
}

void
myfunc3(void)
{
  int j, nptrs;
  void *buffer[SIZE];
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

  char reorg_buff[sizeof(void*) * SIZE + 1];
  reorg_call_bt(buffer, nptrs, reorg_buff);
  print_reorg_bt(reorg_buff);
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

