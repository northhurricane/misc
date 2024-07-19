#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/mman.h>

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
  int temp = (int)((long long)arg);
  printf("thread %d\n", temp);
  if (temp == 1)
  {
    //thread 1
    //local variables memory test
    /*const int local_size = 4*1024*1024;
    char buf[local_size];
    //没有访问申请内存的情况
    //VIRT    RES
    //46644   1104
    memset(buf, 0, local_size);
    //访问内存的情况
    //VIRT    RES
    //46644   5060
    */

    //malloc memory test
    /*
    const int malloc_size(8*1024*1024);
    char *p = (char*)malloc(malloc_size);
    //没有访问申请内存的情况
    //VIRT    RES
    //112180   1100
    for (int i = 0; i < malloc_size; i++)
    {
      p[i] = (i % 26) + 'a';
    }
    //访问内存的情况
    //VIRT    RES
    //112180   9280
    */
    //mmap memory test;
    const int mmap_size = 16*1024*1024;
    char *p2 = nullptr;
    p2 = (char*)mmap(NULL, mmap_size, PROT_READ | PROT_WRITE,
         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    //没有访问申请内存的情况
    //VIRT    RES
    //112180   9280
    for (int i = 0; i < mmap_size; i++)
    {
      p2[i] = (i % 26) + 'a';
    }
    //访问申请内存
    //VIRT    RES
    //63028  17468
  }
  else
  {
    //thread 2
  }

  while (1)
  {
    if (stop_thread)
      break;
    sleep_in_second(1);
  }
  return 0;
}

int
main(int argc, char *argv[])
{
  pthread_t thread;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  const int stack_16m = 16*1024*1024;
  pthread_attr_setstacksize(&attr, stack_16m);

  //default 8M thread stack size
  pthread_create(&thread,&attr,&thread_func,(void*)1);
  //16M thread stack size
  pthread_create(&thread,NULL,&thread_func,(void*)2);

  getchar();
  stop_thread = 1;

  return 0;
}
//g++ mem_test.cc  -o mem_test -lrt -lpthread -std=c++11

