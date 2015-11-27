/*
  g++ test.cc ftrc.cc -o test
*/

#include "ftrc.h"

void func2_1_1()
{
  FUNCTION_TRACE("func2_1_1");
}

void func2_1_2()
{
  FUNCTION_TRACE("func2_1_2");
}

void func1_1()
{
  FUNCTION_TRACE("func1_1");
  func2_1_1();
  func2_1_2();
}

void func2_2_1()
{
  FUNCTION_TRACE("func2_2_1");
}

void func2_2_2()
{
  FUNCTION_TRACE("func2_2_2");
}

void func1_2()
{
  FUNCTION_TRACE("func2_2");
  func2_2_1();
  func2_2_2();
}

int main(int argc, char *argv[])
{
  FUNCTION_TRACE("main");

  func1_1();
  func1_2();
  return 0;
}
