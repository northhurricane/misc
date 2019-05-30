#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct tls_struct
{
  int id;
};
typedef struct tls_struct tls_t;
__thread tls_t tls1;

//class类型需要动态初始化函数

static __thread int my_tls = 0;
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
  long long temp = (long long)arg;
  int second = 0;

  my_tls = (int)temp;
  tls1.id = my_tls;
  if (temp == 1)
    second = 3;
  else
    second = 6;
  printf("my_tls is %d : sleep %d second\n", my_tls, second);
  int count = 0;
  while (1)
  {
    if (stop_thread)
      return NULL;

    printf("thread id %d : select count\n", my_tls, count);
    //tls_c.showme(my_tls);
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

//g++ tls_gcc.cc -o tls_linux -lrt -lpthread
