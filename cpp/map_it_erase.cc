/*
  remove item from map safely
  ref:https://www.cnblogs.com/zhoulipeng/p/3432009.html
*/

#include <iostream>
#include <map>

int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  // try erase item
  for (it=mymap.begin(); it!=mymap.end();)
  {
    if (it->second == 30 || it->second == 50)
    {
      mymap.erase(it++);
      continue;
    }
    std::cout << it->first << " => " << it->second << '\n';
    it++;
  }

  return 0;
}
