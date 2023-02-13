#include <iostream>
#include <unordered_map>
 
int main()
{  
  std::unordered_map<int,char> map = {{1,'a'},{1,'b'},{1,'c'},{2,'b'}};
  std::cout << "map equal" << std::endl;
  auto range = map.equal_range(1);
  for (auto it = range.first; it != range.second; it++) {
    std::cout << it->first << ' ' << it->second << '\n';
  }
  std::cout << "map scan" << std::endl;
  for (auto it = map.begin(); it != map.end(); it++)
  {
    std::cout << it->first << ' ' << it->second << '\n';
  }
    
}
