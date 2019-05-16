/*
#概述
模板分为两种，模板类和模板函数，该代码仅就语法格式进行模板的编写，尝试覆盖大部分的模板
写法。

#模板写法
1、输入参数带有模板
2、输出参数带有模板
3、类成员带有模板

#总结
1、<class T>中T可以是X、Y或其他名字，可以将T理解为C中宏，在进行模板实例化时，实际指定的
类型将替换T
*/
#include <iostream>

using namespace std;

template < class T>
class My_template
{
 public :
  My_template(T v);
  ~My_template();
  T get();
 private:
  T v_m_;
};

template <class T>
My_template<T>::My_template(T v)
{
  v_m_ = v;
}

template <class T>
My_template<T>::~My_template()
{
}

template <class T>
T
My_template<T>::get()
{
  return v_m_;
}

template <class T>
T show_template(T x, T y)
{
  return x + y;
}

int main(const int argc, const char *argv[])
{
  My_template<int> x(1);
  int y = x.get();
  cout << "y is " << y << endl;
  cout << "template func : " << show_template<int>(1, 2) << endl;
  return 0;
}


