/*
show how volatile works
using AT&T style asm syntax
by different optimize level
g++ volatile.cc -o volatile -O0
g++ volatile.cc -o volatile -O2
*/

#include <iostream>

using namespace std;

void test_volatile()
{
  int i = 10;
  int a = i;
  cout << "i = " << a << endl;

  __asm__
  (
    "movl   $0x32,-0x4(%rbp)"
   );

  int b = i;
  cout << "i = " << b << endl;
}

void test_no_volatile()
{
  volatile int i = 10;
  int a = i;
  cout << "i = " << a << endl;

  __asm__
  (
    "movl   $0x32,-0x4(%rbp)"
   );

  int b = i;
  cout << "i = " << b << endl;
}

int main(int argc, const char *argv[])
{
  test_volatile();
  test_no_volatile();

  return 0;
}
