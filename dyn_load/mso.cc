#include <iostream>
#include <ctime>
#include <string>

// 获取当前时间的函数
extern "C" void print_function_name() {
  std::time_t now = std::time(nullptr);
  std::string time_str = std::ctime(&now);
  std::cout << "Current time: " << time_str;
}

// 可选：带返回值的版本
extern "C" const char* get_current_time() {
  std::time_t now = std::time(nullptr);
  return std::ctime(&now);
}


