#include <stdio.h>

class Base
{
public :
  void print()
  {
    printf("base\n");
  }
};

class Derived : public Base
{
public :
  void print()
  {
    printf("derived\n");
  }
};

int main(int argc, char *argv[])
{
  printf("test derived class call\n");
  Derived d;
  Base *bp = &d;
  Derived *dp = &d;

  bp->print();

  dp->print();

  return 0;
}
