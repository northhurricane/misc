/*
使用-finstrument-functions来增加函数进入和退出的附加操作
g++ -g gcc_cyg_prf.cc -o gcc_cyg_prf -finstrument-functions
未定义__cyg_profile_func_enter时，g++ 4.8和10.2并没有按照手册
所描述的行为，只有exit函数，没有enter，同时函数没有参数。按照
gcc手册进行定义，会报告函数重复定义的错误

！！！未能找到正确的使用方式
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/*
导致错误
void __cyg_profile_func_enter (void *this_fn,
                               void *call_site);
*/

static void foo2() {
  cout << "foo2" << endl;
}

void foo1() {
  cout << "foo1" << endl;
  foo2();
}

void foo() {
  cout << "foo" << endl;
  foo1();
}

int main(int argc, const char *argv[]) {
  foo();
  return 0;
}
