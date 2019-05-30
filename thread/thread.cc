// thread example
//g++ thread.cc  -o thread -std=gnu++11 -pthread
#include <iostream>       // std::cout
#include <thread>         // std::thread
 
void foo() 
{
  std::cout << "I'm foo." << std::endl;
}

void bar(int x)
{
  std::cout << "I'm bar." << x << std::endl;
}

void ken(int x, int y)
{
  std::cout << "I'm ken." << x << y << std::endl;
}

int main() 
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0);  // spawn new thread that calls bar(0)
  std::thread third (ken,0, 1);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes
  third.join();

  std::cout << "foo and bar completed.\n";

  return 0;
}

