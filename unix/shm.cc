/*
g++ shm.cc -o shm -g -O0
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
    cout << "please input message.";
    cin >> cmd;
    if (cmd == "q")
      break;
    //拷贝数据至共享内存区
    cout << shmadd;
  }
  {
    //读共享内存区数据
    printf("data = [%s]\n", shmadd);
  }
  
  //分离共享内存和当前进程
  ret = shmdt(shmadd);
  if(ret < 0)
  {
    perror("shmdt");
    exit(1);
  }
  else
  {
    printf("deleted shared-memory\n");
  }
  //删除共享内存
  shmctl(shmid, IPC_RMID, NULL);
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
