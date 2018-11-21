#include <string>
#include <iostream>

using namespace std;

class C1
{
public :
  C1(const char *s) :s_(s)
  {
  }
  void set(const string &v)
  {
    s_ = v;
  }
  string get() const //function can be called by const variable
  {
    return s_;
  }
private :
  string s_;
};

int main(int argc, const char *argv[])
{
  const C1 c1("const");
  //c1.set("new"); //compile failed
  static_cast<C1>(c1).set("new");
  cout << "static_cast " << c1.get() << endl;
  const_cast<C1&>(c1).set("new2");
  cout << "const_cast " << c1.get() << endl;
  return 0;
}
