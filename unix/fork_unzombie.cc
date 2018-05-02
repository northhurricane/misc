/*
根据UNIX环境高级编程图8-8的例子进行改写。
该例子的目的是实现：如果一个进程fork一个子进程，但不要它等待子进程终止，也不希望子进程处于僵死状态直到父进程终止，实现这一要求的诀窍是调用fork两次。
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  pid_t pid;

  if ((pid = fork()) < 0)
  {
    printf("fork error.\n");
  }
  else if (pid == 0)
  {
    if ((pid = fork()) < 0)
      printf("fork error.\n");
    else if (pid > 0)
    {
      sleep(10);
      printf("child exit.\n");
      exit(0);
    }
    sleep(20);
    printf("second child, parent pid = %ld\n", (long)getppid());
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid)
    printf("waitpid error.\n");

  sleep(10);
  printf("main exit.\n");
  exit(0);
}
