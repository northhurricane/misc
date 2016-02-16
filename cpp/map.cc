#include <map>
#include <string>

using namespace std;

typedef map<string, int> string_int_map_t;
typedef string_int_map_t::iterator string_int_map_it_t;

int main(int argc, char *argv[])
{
  string_int_map_t name_age_map;
  //插入数据
  name_age_map["mary"] = 23;
  name_age_map["john"] = 32;
  string name = "jack";
  int age = 0;
  //查找数据
  string_int_map_it_t it = name_age_map.find(name);
  if (it == name_age_map.end())
  {
    //not found
  }
  else
  {
    //found
    age = it->second;
    //删除数据
    name_age_map.erase(it);
  }

  return 0;
}
