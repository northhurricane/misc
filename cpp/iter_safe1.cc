/*
  iterator from same 
*/
#include <list>
#include <iostream>

using namespace std;

int main(int argc, const char *argv[])
{
  list<int> li;
  for (int i = 0; i < 10; i++)
    li.push_back(i);

  list<int>::iterator it1;

  it1 = li.begin();
  it1++;
  cout << "it1 is : " << *it1 << endl;

  list<int>::iterator it2;
  it2 = li.begin();
  it2++; it2++;

  it1++;
  cout << "it1 is : " << *it1 << endl;

  return 0;
}
