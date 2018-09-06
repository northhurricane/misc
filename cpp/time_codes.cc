/*
Common time opertions
*/

#include <time.h>

#include <unistd.h>
#include <stdio.h>

/*
C99 time function
*/
/*get current time*/
void
c99_get_current_time()
{
  time_t now = time(0);
}

/**/
void
c99_time_diff()
{
  time_t t1 = time(0);
  sleep(3);
  time_t t2 = time(0);
  printf("interval between %d.\n", (int)difftime(t2, t1));
}


int main(int argc, char *argv[])
{
  c99_time_diff();
  return 0;
}
