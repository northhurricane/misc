/*
  用于模拟new/delete操作
*/
#include <iostream>
#include <stdlib.h>

using namespace std;

class X
{
public :
  X()
  {
    cout << "constructor X" << endl;
  }
  ~X()
  {
    cout << "deconstructor X" << endl;
  }
  virtual void show() = 0;
};

class X1 : public X
{
public :
  X1()
  {
    cout << "constructor X1" << endl;

  }
  void show ()
  {
    cout << "I am X1" << endl;
  }
  ~X1()
  {
    cout << "deconstructor X1" << endl;
  }
};

int main(int argc, const char *argv[])
{
  X1 *x1 = (X1*)malloc(sizeof(X1));
  new (x1) X1;
  x1->show();
  x1->~X1();
  free(x1);
  return 0;
}


