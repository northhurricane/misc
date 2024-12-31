/*
  g++ cas_cost.cc -o cas_cost -lpthread
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>

#define NUM_THREADS 3
#define NUM_ITERATIONS 10000000

using namespace std;

volatile int atomicInteger = 0;

// 计算两个timespec结构体之间的时间间隔
struct timespec diff_timespec(struct timespec beg, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec - beg.tv_nsec) < 0) {
    temp.tv_sec = end.tv_sec - beg.tv_sec - 1;
    temp.tv_nsec = 1000000000 + end.tv_nsec - beg.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec - beg.tv_sec;
    temp.tv_nsec = end.tv_nsec - beg.tv_nsec;
  }
  return temp;
}

void* CASWorker(void* arg) {
  int local_tid = *((int*)arg);
  // 获取当前时间
  struct timespec ts_beg;
  if (clock_gettime(CLOCK_REALTIME, &ts_beg) != 0)
  {
    perror("clock_gettime");
    return (void*)1;
  }
  for (int i = 0; i < NUM_ITERATIONS; i++) {
    int expected, desired;
    do {
      expected = atomicInteger;
      desired = expected + 1;
    } while (!__sync_bool_compare_and_swap(&atomicInteger, expected, desired));
  }
  // 获取当前时间
  struct timespec ts_end;
  if (clock_gettime(CLOCK_REALTIME, &ts_end) != 0)
  {
    perror("clock_gettime");
    return (void*)1;
  }
  struct timespec interval = diff_timespec(ts_beg, ts_end);
  printf("Cost time: %ld.%09ld seconds\n",
         interval.tv_sec , interval.tv_nsec);
  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];

  cout << "Current thread number is " << NUM_THREADS << endl;
  // 创建线程
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, CASWorker, &i) != 0) {
      perror("Failed to create thread");
      return 1;
    }
  }

  // 等待所有线程完成
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Failed to join thread");
      return 1;
    }
  }

  printf("Final value: %d\n", atomicInteger);
  return 0;
}

