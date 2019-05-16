/*
#概述
了解函数对象的语法和运行机制

#定义
任何定义了函数调用操作符的对象都是函数对象

*/
#include <iostream>

using namespace std;

class func_obj
{
public :
  int operator () ()
  {
    return 1;
  }
  int operator ()  (int v)
  {
    return v;
  }
};

int main(int argc, const char *argv[])
{
  func_obj fo;
  int i = fo();
  cout << "fo() result : " << i << endl;

  func_obj fo2;
  i = fo2(10);
  cout << "fo(10) result : " << i << endl;

  return 0;
}
