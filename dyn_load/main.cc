#include <iostream>
#include <dlfcn.h> // 动态加载库的头文件

//测试动态加载函数的问题
//g++ -O0 -o main main.cc -ldl
//g++ -shared -fPIC -o libmso.so mso.cc

// 定义一个函数，打印自身的函数名
extern "C" void print_function_name() {
  std::cout << "Current function: " << __func__ << std::endl;
}

typedef void (*Print_func)(); // 函数指针类型

int main() {
  std::cout << "Program started." << std::endl;

  void* handle = dlopen("./libmso.so", RTLD_LAZY);
  if (!handle) {
    std::cerr << "Failed to load library: " << dlerror() << std::endl;
    return 1;
  }
  Print_func print_func = (Print_func)dlsym(handle, "print_function_name");
  print_function_name();  // 调用函数，打印函数名
  print_func();

  dlclose(handle);
  std::cout << "Program ended." << std::endl;
  return 0;
}
