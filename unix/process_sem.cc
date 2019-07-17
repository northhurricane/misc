/*
g++ process_sem.cc -o process_sem -lpthread -g -O0
sem_unlink 从系统中将该名字semaphore移除，在名字被移除后，sem依旧可以使用。
*/

#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

#define SEM_NAME   "my_sem"

static void process_producer()
{
  cout << "enter producer process" << endl;
  sem_t *sem = NULL;
  sem = sem_open(SEM_NAME, O_CREAT|O_RDWR, 0666, 0);
  if (sem == NULL)
  {
    cout << "fail open sem." << endl;
    exit(-1);
  }

  string cmd;
  int r = 0;
  //bool unlinked = false;
  while (true)
  {
    cout << "please input message." << endl;
    cin >> cmd;
    if (cmd == "q")
      break;
    cout << "sem post" << endl;
    r = sem_post(sem);
    if (r < 0)
      cout << "fail post" << endl;
    /*
    if (!unlinked)
    {
      r = sem_unlink(SEM_NAME);
      if (r < 0)
        cout << "failed unlink." << endl;
    }
    */
  }
  r = sem_unlink(SEM_NAME);
  if (r < 0)
    cout << "failed unlink." << endl;
  r = sem_close(sem);
  if (r < 0)
    cout << "failed close." << endl;

  exit(0);
}

static void process_consumer()
{
  cout << "enter consumer process" << endl;

  sem_t *sem = NULL;
  sem = sem_open(SEM_NAME, O_CREAT|O_RDWR, 0666, 0);
  if (sem == NULL)
  {
    cout << "fail open sem." << endl;
    exit(-1);
  }

  string cmd;
  int r = 0;
  while (true)
  {
    cout << "please input message." << endl;
    cin >> cmd;
    if (cmd == "q")
      break;
    cout << "sem wait" << endl;
    r = sem_wait(sem);
  }
  r = sem_unlink(SEM_NAME);
  if (r < 0)
    cout << "failed unlink." << endl;
  r = sem_close(sem);
  if (r < 0)
    cout << "failed close." << endl;

  exit(0);
}

int main(int argc, const char *argv[])
{
  if (argc == 1)
  {
    process_producer();
  }
  else
  {
    process_consumer();
  }

  return 0;
}
