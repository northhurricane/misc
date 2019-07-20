/*
g++ shm.cc -o shm -g -O0
1、还有进程未detach，调用shmctl删除共享内存也不会真正删除，直至所有进程完成detach
2、同一key的共享内存不能重复删除
3、detach在进程结束后自动完成
ref
1,https://blog.csdn.net/tennysonsky/article/details/46425485
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <iostream>
#include <string>
#include <errno.h>

using namespace std;


#define BUFSZ (1024 * 1024 * 8)
#define SHM_KEY "./my_key1"
#define SHM_PROJ_ID (6033)

static void write_process()
{
  int shmid;
  int ret;
  key_t key;
  char *shmadd;
  
  cout << "share memory test write process" << endl;
  //创建key值
  key = ftok(SHM_KEY, SHM_PROJ_ID);
  if(key == -1)
  {
    perror("ftok");
  }
  
  //创建共享内存
  shmid = shmget(key, BUFSZ, IPC_CREAT|0666);
  if(shmid < 0) 
  { 
    perror("shmget"); 
    exit(-1); 
  }
  
  //映射
  shmadd = (char*)shmat(shmid, NULL, 0);
  if(shmadd < 0)
  {
    perror("shmat");
    _exit(-1);
  }

  //拷贝数据至共享内存区
  string cmd;
  while (true)
  {
    cout << "please input message." << endl;
    cin >> cmd;
    if (cmd == "q")
      break;
    //拷贝数据至共享内存区
    strcpy(shmadd, cmd.c_str());
    shmadd[cmd.length()] = 0;
  }

  //分离共享内存和当前进程
  ret = shmdt(shmadd);
  if(ret < 0)
  {
    cout << "failed detach.error code " << errno << endl;
    exit(1);
  }
  else
  {
    printf("detached shared-memory\n");
  }
  //删除共享内存
  ret = shmctl(shmid, IPC_RMID, NULL);
  if (ret < 0)
    cout << "shmctl remove failed.errro #" << errno << endl;
  else
    cout << "shcmctl remove shared-memory" << endl;
}

static void read_process()
{
  int shmid;
  int ret;
  key_t key;
  char *shmadd;

  cout << "share memory test read process" << endl;
  //创建key值
  key = ftok(SHM_KEY, SHM_PROJ_ID); 
  if(key == -1)
  {
    perror("ftok");
  }
  
  //打开共享内存
  shmid = shmget(key, BUFSZ, IPC_CREAT|0666);
  if(shmid < 0) 
  { 
    perror("shmget"); 
    exit(-1); 
  } 
  
  //映射
  shmadd = (char*)shmat(shmid, NULL, 0);
  if(shmadd < 0)
  {
    perror("shmat");
    exit(-1);
  }

  string cmd;
  while (true)
  {
    cout << "please input message." << endl;
    cin >> cmd;
    if (cmd == "q")
      break;
    //拷贝数据至共享内存区
    cout << shmadd;
  }
  
  //分离共享内存和当前进程
  ret = shmdt(shmadd);
  if(ret < 0)
  {
    cout << "failed detach.error code " << errno << endl;
    exit(1);
  }
  else
  {
    cout << "detached shared-memory" << endl;
  }
  //删除共享内存
  ret = shmctl(shmid, IPC_RMID, NULL);
  if (ret < 0)
    cout << "shmctl remove failed.errro #" << errno << endl;
  else
    cout << "shcmctl remove shared-memory" << endl;
}

int main(int argc, const char *argv[])
{
  if (argc == 1)
  {
    write_process();
  }
  else
  {
    read_process();
  }
  return 0;
}
