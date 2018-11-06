#include <iostream>
#include <string>

//test if class constructor and de-constructor will be called in struct

using namespace std;

class C
{
public :
  C() { cout << "C cons" << endl; }
  ~C() { cout << "C decons" << endl; }
};

struct st
{
  string s;
  C c;
};

int main(int argc, char *argv[])
{
  struct st st1;
  st1.s = "abc";
  return 0;
}
