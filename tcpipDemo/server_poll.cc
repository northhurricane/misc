#include <iostream>
#include <sys/socket.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

#define SERVPORT 5667  /* 服务器监听端口号 */
#define BACKLOG 10    /* 最大同时连接请求数 */

int process_new_connection(int sockfd)
{
  int r = 0;
  struct pollfd fds;
  memset(&fds, 0 , sizeof(fds));
  fds.fd = sockfd;
  fds.events = POLLIN;
  while (true)
  {
    r = poll(&fds, 1, 10);
    if (r < 0)
    {
      cout << "poll fail. error no : " << errno << endl;
      return -1;
    }
    if(fds.revents == 0)
      continue;
    if(fds.revents == POLLIN)
      break;
  }

  struct sockaddr_in remote_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  int client_sockfd;

  client_sockfd = accept(sockfd, (struct sockaddr*) &remote_addr, &sin_size);

  if (client_sockfd == -1)
  {
    perror("accept");
    exit(1);
  }
  return client_sockfd;
}

int process_exist_connection(int client_sockfd)
{
  int len = 0;
  char recv_buf[300];
  char send_buf[250];

  //while (true)
  {
    len = recv(client_sockfd, recv_buf, sizeof(recv_buf), 0);
    if (len <= 0)
      return len;

    recv_buf[len] = 0;
  }

  cout << "client said " << recv_buf << endl;
  sprintf(send_buf, "heared you say %s", recv_buf);
  len = send(client_sockfd, send_buf, strlen(send_buf), 0);
}

int init_sock(short port)
{
  int sockfd;
  struct sockaddr_in my_addr;

  if ((sockfd = socket(AF_INET,  SOCK_STREAM,  0)) == -1) 
  {
    perror("socket failed");
    exit(1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;

  bzero(&(my_addr.sin_zero), 8);
  if (bind(sockfd,  (struct sockaddr *)&my_addr,  sizeof(struct sockaddr)) == -1) 
  {
    char errmsg[1024];
    sprintf(errmsg, "binding failed.errno:%d\n", errno);
    perror(errmsg);
    exit(1);
  }
  cout << "bind ok" << endl;

  if (listen(sockfd,  BACKLOG) == -1)
  {
    perror("listenning failed");
    exit(1);
  }

  return sockfd;
}

int main()
{
  int sockfd = init_sock(SERVPORT);
  int clientfd = process_new_connection(sockfd);
  //不断读取数据
  while (true)
  {
    int r = process_exist_connection(clientfd);
    if (r <= 0)
      break;
  }
  close(clientfd);
  close(sockfd);

  return 0;
}

