#include <cstdio>
//#include <atomic>

using namespace std;

int main(int argc, const char* argv[])
{
  int v1 = 0, v2 = 1;
  int curr = v1;
  //bool r = atomic_compare_exchange_weak(&v1, &curr, v2);
  bool r = __sync_bool_compare_and_swap(&v1, curr, v2);
  if (r)
    printf("change success.now is %d\n", v1);
  else
    printf("change fail.now is %d", v1);
  return 0;
}
