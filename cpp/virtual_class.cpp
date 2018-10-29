/*
show how "dreaded diamond" inheritance work
ref:
https://en.wikipedia.org/wiki/Virtual_inheritance
https://isocpp.org/wiki/faq/multiple-inheritance
*/
#include <iostream>

using namespace std;

class A
{
public :
  A()
  {
    cout << "A construct" << endl;
    v1 = 0;
  }

  int v1;
  char v2[1024];
};

class B : public A
{
public :
  B()
  {
    cout << "B construct" << endl;
  }
};

class C : public A
{
public :
  C()
  {
    cout << "C construct" << endl;
  }
};

class D : public B, public C
{
public :
  D()
  {
    cout << "D construct" << endl;
  }
  void show_me()
  {
    cout << "I'm D. Value is " << B::v1 << endl;
  }
};

class B2 : public virtual A
{
public :
  B2()
  {
    cout << "B2 construct" << endl;
  }
};

class C2 : public virtual A
{
public :
  C2()
  {
    cout << "C2 construct" << endl;
  }
};

class D2 : public B2, public C2
{
public :
  D2()
  {
    cout << "D2 construct" << endl;
  }
  void show_me()
  {
    cout << "I'm D. Value is " << v1 << endl;
  }
};

int main(int argc, char *argv[])
{
  D d;
  d.show_me();
  cout << "D size is " << sizeof(D) << endl;
  cout << "=====" << endl;
  D2 d2;
  d2.show_me();
  cout << "D2 size is " << sizeof(D2) << endl;
  return 0;
}
