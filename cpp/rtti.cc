#include <stdio.h>
#include <typeinfo>

class Base
{
public :
  void print()
  {
    printf("Base\n");
  }
  virtual void print(int i)
  {
    printf("Base %d\n" , i);
  }
};

class Derived : public Base
{
public :
  void print()
  {
    printf("Derived\n");
  }
  virtual void print(int i)
  {
    printf("Derived %d\n" , i);
  }
};

void
test_dynamic_cast()
{
  Base b;
  Derived d;
  Base *bp = &b;
  Base * bdp = &d;
  Derived *dp = 0;

  dp = dynamic_cast<Derived*>(bdp);
  if (dp != 0)
  {
    printf("derived object's base pointer convert to derived object pointer\n");
  }

  dp = dynamic_cast<Derived *>(bp);
  if (dp != 0)
  {
  }
}

void
test_typeid()
{
  Base b;
  Derived d;
  Base *bp = &b;
  Base * bdp = &d;
  Derived *dp = &d;

  if (typeid(*bdp) == typeid(*dp))
  {
    printf("same object.different pointer.different type.\n");
  }

  if (typeid(*bdp) == typeid(Derived))
  {
    printf("same object.base pointer.different type.\n");
  }
}

int main (int argc, char *argv[])
{
  test_typeid();

  return 0;
}
