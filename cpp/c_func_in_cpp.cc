#include <iostream>

using namespace std;

void func_cpp()
{
  cout << "function in cpp called by c" << endl;
}

extern "C" void func();
void func()
{
  func_cpp();
}

