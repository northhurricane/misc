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

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdint.h>
void
posix_timer()
{
  struct timespec time_start={0, 0},time_end={0, 0};
  clock_gettime(CLOCK_REALTIME, &time_start);
  sleep(1);
  clock_gettime(CLOCK_REALTIME, &time_end);
  uint64_t duration = (time_end.tv_sec - time_start.tv_sec) * 1000000000
                      + (time_end.tv_nsec-time_start.tv_nsec);
  std::cout << "duration is " << duration << std::endl;
}

int main(int argc, char *argv[])
{
  //c99_time_diff();
  posix_timer();
  return 0;
}
