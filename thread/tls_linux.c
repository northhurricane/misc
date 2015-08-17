#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static __thread int randnum = 0;
static int stop_thread = 0;

int sleep_in_second(int n)
{
  struct timespec time_to_sleep, time_real_sleep;

  time_to_sleep.tv_sec = n;
  time_to_sleep.tv_nsec = 0;
  nanosleep(&time_to_sleep, &time_real_sleep);
}

static void* thread_func(void *arg)
{
  int number = (int)(void*)arg;
  int second = 0;

  if (number == 1)
    second = 3;
  else
    second = 6;
  while (1)
  {
    if (stop_thread)
      return NULL;

    printf("thread %d : select %d second\n", number, second);
    sleep_in_second(second);
  }
}

int
main(int argc, char *argv[])
{
  pthread_t thread;

  pthread_create(&thread,NULL,&thread_func,(void*)1);
  pthread_create(&thread,NULL,&thread_func,(void*)2);

  getchar();
  stop_thread = 1;

  return 0;
}

//gcc tls_linux.c -o tls_linux -lrt
