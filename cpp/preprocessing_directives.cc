#include <iostream>

using namespace std;

void test_line()
{
  cout << "test_line" << endl;
#line 1 "preprocessing_directives.line"
  int i = 0;
#line 11 "preprocessing_directives.cc"
  {
    i++;
  }
}

int main(int argc, const char *argv[])
{
  test_line();

  cout << "return to main" << endl;

  return 0;
}
