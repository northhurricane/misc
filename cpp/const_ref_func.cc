#include <stdio.h>

class Obj
{
public :
  const int &GetCount() { return count_; }
  int *GetCountPtr() { return &count_; }
private :
  int count_;
};

int main(int argc, char *argv[])
{
  Obj o;
  const int &c = o.GetCount();
  int *pc = o.GetCountPtr();
  printf("GetCount    pointer:%p\n", &c);
  printf("GetCountPtr pointer:%p\n", pc);
  return 0;
}
