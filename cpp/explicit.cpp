/*
如下例所示，当构造函数只有一个参数，可通过隐式数据类型转换进行构造，该方式会产生额外的代码。
B b = 1;
该行代码将会被改写为
B tmp(1);
B b(tmp);
~tmp();
*/

#include <iostream>

using namespace std;

class A
{
public :
  explicit A(int v) : v_(v)
  {
  }
  void show_me()
  {
    cout << v_ << endl;
  }
private :
  int v_;
};

class B
{
public :
  B(int v) : v_(v)
  {
  }
  void show_me()
  {
    cout << v_ << endl;
  }
private :
  int v_;
};

class C
{
public :
  C(B v) : v_(v)
  {
  }
  void show_me()
  {
    v_.show_me();
  }
private :
  B v_;
};


int main(int argc, char *argv[])
{
  A a(1);
  a.show_me();
  //compile failed
  /*A a = 1;
    a.show_me();*/

  B b = 1;
  b.show_me();

  C c = b;
  c.show_me();

  //compile failed
  //C c2 = 1;
  return 0;
}
