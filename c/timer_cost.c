#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

#define TEST_COUNT 100000000

void benchmark_time() {
  clock_t start = clock();

  for (int i = 0; i < TEST_COUNT; i++) {
    time_t t = time(NULL);
  }

  clock_t end = clock();
  printf("time(): %ld 时钟周期\n", end - start);
}

void benchmark_gettimeofday() {
  clock_t start = clock();
  struct timeval tv;

  for (int i = 0; i < TEST_COUNT; i++) {
    gettimeofday(&tv, NULL);
  }

  clock_t end = clock();
  printf("gettimeofday(): %ld 时钟周期\n", end - start);
}

void benchmark_clock_gettime() {
  clock_t start = clock();
  struct timespec ts;

  for (int i = 0; i < TEST_COUNT; i++) {
    clock_gettime(CLOCK_REALTIME, &ts);
  }

  clock_t end = clock();
  printf("clock_gettime(): %ld 时钟周期\n", end - start);
}

int main(int argc, const char *argv[])
{
  benchmark_time();
  benchmark_gettimeofday();
  benchmark_clock_gettime();
  return 0;
}
