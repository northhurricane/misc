/*
g++ fork_example.cc -o fork_example
最简单的fork调用
通过pos N来说明代码在那个进程中执行
*/
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  pid_t pid;

  printf("code pos 1, getpid()=%d\n",getpid());
  if ((pid = fork()) < 0)
  {
    printf("fork error.\n");
    exit(-1);
  }
  if (pid == 0)
  {
    sleep(5);
    printf("code pos 2, getpid()=%d\n",getpid());
    printf("code pos 4, getppid()=%d\n",getppid());
    printf("child exit.\n");
    exit(0);
  }

  printf("code pos 3, getpid()=%d\n",getpid());
  if (waitpid(pid, NULL, 0) != pid)
    printf("waitpid error.\n");

  printf("parent exit.\n");
  exit(0);
}
