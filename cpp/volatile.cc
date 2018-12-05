/*
show how volatile works

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
    "mov dword ptr [ebp-4], 20"
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
    "mov dword ptr [ebp-4], 20"
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
