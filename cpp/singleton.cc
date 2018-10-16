/*
ref:
https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
http://blog.yangyubo.com/2009/06/04/best-cpp-singleton-pattern/
*/

//test under g++ (GCC) 4.8.5

#include <iostream>

using namespace std;

class Singleton
{
public :
  static Singleton *getInstance();
  void showMe();
private :
  Singleton();
  ~Singleton();

  static Singleton _instance;
  static int a;
  //  static void *p;
};

Singleton *Singleton::getInstance()
{
  return &_instance;
}

void Singleton::showMe()
{
  cout << "It's me." << endl;
}

Singleton::Singleton()
{
  cout << "init" << endl;
}

Singleton::~Singleton()
{
  cout << "deinit" << endl;
}

int Singleton::a = 0;
Singleton Singleton::_instance;

int main(int argc, const char *argv[])
{
  Singleton::getInstance()->showMe();
  return 0;
}
