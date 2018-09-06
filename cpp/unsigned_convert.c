#include <stdint.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
  int32_t i = -1;
  uint32_t ui = (uint32_t)i;
  uint32_t *pui = (uint32_t*)&i;
  printf("direct convert is %d. pointer convert is %d\n", ui, *pui);
  return 0;
}
