#include <pthread.h>
#include <iostream>
#include <stdint.h>
#include <time.h>

/*
g++ spinlock.cc -o spinlock -lpthread
*/

using namespace std;

pthread_spinlock_t spinlock;

pthread_t thread1, thread2;

void* spinthread1(void *para)
{
  cout << "thread 1 started" << endl;
  pthread_spin_lock(&spinlock);
  cout << "thread 1 enter spin lock" << endl;
  for (uint64_t i = 1; i <= 100000000000000; i++)
  {
  }
  pthread_spin_unlock(&spinlock);
  return 0;
}

void* spinthread2(void *para)
{
  struct timespec time_to_sleep, time_real_sleep;
  time_to_sleep.tv_sec = 2;
  time_to_sleep.tv_nsec = 0;
  nanosleep(&time_to_sleep, &time_real_sleep);

  cout << "thread 2 started" << endl;
  pthread_spin_lock(&spinlock);
  cout << "thread 2 enter spin lock" << endl;
  pthread_spin_unlock(&spinlock);
  return 0;
}

void startspinthread1()
{
  int number = 1, r = 0;

  r = pthread_create(&thread1,NULL,&spinthread1,&number);
  if (r != 0)
    cout << "start thread 1 fail" << endl;
}

void startspinthread2()
{
  int number = 2, r = 0;

  r = pthread_create(&thread2,NULL,&spinthread2,&number);
  if (r != 0)
    cout << "start thread 2 fail" << endl;
}

int main(int argc, char *argv[])
{
  int r;
  r = pthread_spin_init(&spinlock, 0);
  if (r != 0)
  {
    cout << "init failed" << endl;
    return r;
  }

  //开始spin1的线程
  startspinthread1();
  //开始spin2的线程
  startspinthread2();

  void *result1, *result2;
  pthread_join(thread1,&result1);
  pthread_join(thread2,&result2);

  r = pthread_spin_destroy(&spinlock);

  if (r != 0)
  {
    cout << "destroy failed" << endl;
    return r;
  }

  return 0;
}
