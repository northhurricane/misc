#include <stdio.h>
#include <time.h>

#define NANO_RATE (1000*1000*1000)
//纳秒
int sleep_in_nano(long n)
{
  struct timespec time_to_sleep, time_real_sleep;
  long sec, nsec;
  sec = n / NANO_RATE;
  nsec = n % NANO_RATE;

  time_to_sleep.tv_sec = sec;
  time_to_sleep.tv_nsec = nsec;
  return nanosleep(&time_to_sleep, &time_real_sleep);
}

//微秒
int sleep_in_micro(long n)
{
  return sleep_in_nano(1000 * n);
}

//毫秒
int sleep_in_milli(long n)
{
  return sleep_in_micro(1000 * n);
}

//秒
int sleep_in_second(long n)
{
  return sleep_in_milli(1000 * n);
  /*  struct timespec time_to_sleep, time_real_sleep;

  time_to_sleep.tv_sec = n;
  time_to_sleep.tv_nsec = 0;
  return nanosleep(&time_to_sleep, &time_real_sleep);*/
}

int main(int argc, char *argv[])
{
  int r;
  printf("before sleep\n");
  r = sleep_in_second(3);
  printf("sleep return %d\n", r);
  printf("after sleep\n");
}
