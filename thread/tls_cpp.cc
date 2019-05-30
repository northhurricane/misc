// thread_local example
//g++ tls_cpp.cc -o tls_cpp -std=gnu++11 -pthread
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <sstream>

struct tls_struct
{
  int id;
};
typedef struct tls_struct tls_t;

class Tls
{
 public :
  Tls()
  {
    std::cout << "class Tls" << std::endl;
  }
  void set_id(int id_) {id = id_;}
 private :
  int id;
};

thread_local tls_t tls_info;
thread_local Tls tls_info2;
thread_local int tls_id = -1;
thread_local std::string tls_name;
 
void bar(int x)
{
  std::stringstream stream;
  tls_id = x;
  tls_info.id = tls_id;
  tls_name = "bar";
  stream << "I'm bar. My id is " << tls_id << " and struct id " << tls_info.id
         << " and name " << tls_name << std::endl;
  std::string out;
  std::cout << stream.str();
}

void ken(int x)
{
  std::stringstream stream;
  tls_id = x;
  tls_info.id = tls_id;
  tls_name = "ken";
  stream << "I'm ken. My id is " << tls_id << " and struct id " << tls_info.id
         << " and name " << tls_name << std::endl;
  std::cout << stream.str();
}

int main() 
{
  std::thread second (bar, 1);  // spawn new thread that calls bar(0)
  std::thread third (ken, 2);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  second.join();               // pauses until second finishes
  third.join();

  std::cout << "foo and bar completed.\n";

  return 0;
}
