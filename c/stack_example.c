// stack_example.c
#include <stdio.h>

// 第二层函数
void function_b(int param_b) {
  int local_b = param_b * 2;
  printf("In function_b: param_b=%d, local_b=%d\n", param_b, local_b);
  // 在这里设置断点
}

// 第一层函数
void function_a(int param_a) {
  int local_a = param_a + 10;
  printf("In function_a: param_a=%d, local_a=%d\n", param_a, local_a);
  function_b(local_a);  // 调用第二层函数
}

// 主函数
int main(int argc, char *argv[]) {
  int main_var = 5;
  printf("In main: main_var=%d\n", main_var);
  function_a(main_var);  // 调用第一层函数
  return 0;
}

//gcc -g -o stack_example stack_example.c 
