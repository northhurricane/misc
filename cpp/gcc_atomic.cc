#include <stdio.h>

int main(int argc, const char * const argv[])
{
  long long count = 0;
  __sync_fetch_and_add(&count,1);
  printf("now is %ld", count);
  return 0;
}
