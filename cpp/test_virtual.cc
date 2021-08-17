/*
  虚函数的函数指针保存于类对象的虚函数表中，非虚函数的函数指针为全局
  a->vf，使用的是a对象的虚函数表中的函数指针进行调用
  a->nvf，使用的nvf的函数指针进行调用
  对于虚函数，要在运行时定找到函数指针，进行调用；对于非虚函数，在编译期就可以的确定
  其函数指针，进行调用
  依据是否定义了virtual，可以确定非虚函数

  g++ -std=c++11
*/

#include <iostream>

using namespace std;

class Base
{
public :
  virtual void vf() {cout << "Base" << endl; }
  void nvf() {cout << "Base" << endl; }
};

class Derived : public Base
{
public :
  virtual void vf() {cout << "Derived" << endl; }
  void nvf() { cout << "Derived" << endl; }
};

int main(int argc, const char *argv[])
{
  Base b;
  Base *bp = new Derived();

  bp->vf();  //调用Derived的函数
  bp->nvf(); //调用Base的函数

  return 0;
}
