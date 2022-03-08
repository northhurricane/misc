//g++ catch_test.cc -o catch_test
#include <iostream>

using namespace std;

int main(const int argc, const char *argv[])
{
  try {
    char * A = 0;
    A[0] = 1;
  }
  catch (...) {
    cout << "NULL point access catched. Impossible!!!";
  }
  return 0;
}
