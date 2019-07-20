/*
g++ check_process_exist.cc -o check_process_exist -g -O0
*/
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <errno.h>

using namespace std;

int child_process(const char *info)
{
  cout << "child process with info : " << info << "." << endl;

  while (true)
  {
    sleep(5);
    cout << "child process sleep." << endl;
  }

  return 0;
}

int main(int argc, const char *argv[])
{
  string info;
  cout << "check process exist by pid." << endl;

  cin >> info;
  pid_t pid = fork();
  if (pid == 0)
  {
    child_process(info.c_str());
  }
  else
  {
    int r = kill(pid, 0);
    if (r == 0)
      cout << "process " << pid << " exist." << endl;
    else if (r == ESRCH)
      cout << "process " << pid << " does not exist." << endl;
    else
      cout << "error #" << errno << " returned" << endl;

    cin >> info;
    r = kill(pid, SIGKILL);
    if (r < 0)
      cout << "kill process " << pid << " failed. error #" << errno << endl;
    else
      cout << "kill process " << pid << " succeeded." << endl;
  }

  return 0;
}

