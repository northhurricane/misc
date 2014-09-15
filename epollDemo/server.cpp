#include <sys/epoll.h>
#include <iostream>
#include <fcntl.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;

#define SERVPORT 9527 /* 服务器监听端口号 */
#define EPOLLHINT 10  /* create_epoll参数 */
#define BACKLOG 10    /* 最大同时连接请求数 */

void set_nonblocking(int sock)
{
  int opts;

  opts = fcntl(sock,F_GETFL);
  if (opts < 0)
  {
    perror("fcntl(sock,GETFL)");
    exit(1);
  }
  opts = opts|O_NONBLOCK;
  if(fcntl(sock,F_SETFL,opts)<0)
  {
    perror("fcntl(sock,SETFL,opts)");
    exit(1);
  }
}

int process_new_connection(int sockfd)
{
  struct sockaddr_in remote_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  int client_sockfd;

  client_sockfd = accept(sockfd, (struct sockaddr*) &remote_addr, &sin_size);

  if (client_sockfd == -1)
  {
    perror("accept");
    exit(1);
  }
}

void process_exist_connection(int client_sockfd)
{
  int len, total_len = 0;
  char recv_buf[200];
  char send_buf[250];
  char tmp_buf[100];

  while ((len = recv(client_sockfd, tmp_buf, sizeof(tmp_buf), 0)) > 0)
  {
    memcpy(recv_buf + total_len, tmp_buf, len);
    total_len += len;
  }
  
  recv_buf[total_len] = 0;
  if (len == 0)
  {
    //client close socket orderly. this socket should be removed from epoll
  }

  cout << "client said " << recv_buf << endl;
  sprintf(send_buf, "heared you say %s", recv_buf);
  len = send(client_sockfd, send_buf, strlen(send_buf), 0);
}

void add_client_to_epoll(int epollfd, int client_sockfd)
{
  struct epoll_event ev;

  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = client_sockfd;

  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client_sockfd, &ev) == -1)
  {
    perror("epoll_ctl failed add client connected socket");
    exit(1);
  }
}

void remove_client_from_epoll(int epollfd, int client_sockfd)
{
  struct epoll_event event = {0, {0}};
  
  int r = epoll_ctl(epollfd, EPOLL_CTL_DEL, client_sockfd, &event);
  if (r != 0)
  {
    cout << "remvoe event failed" ;
  }
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
    perror("binding failed");
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

int init_epoll(int sockfd)
{
  int epollfd;
  struct epoll_event ev;

  epollfd = epoll_create(EPOLLHINT);
  ev.events = EPOLLIN;
  ev.data.fd = sockfd;

  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1)
  {
    perror("epoll_ctl for socket fail");
    exit(1);
  }

  cout << "epoll_create ok" << endl;

  return epollfd;
}

#define MAX_EVENTS 10

int main()
{
  cout << "begin epoll server" << endl;

  int sockfd = init_sock(SERVPORT);
  int epollfd = init_epoll(sockfd);

  int nfds = 0;
  struct epoll_event events[MAX_EVENTS];
  while (true)
  {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);

    if (nfds == -1)
    {
      perror("epoll_pwait failed");
      exit(1);
    }

    for (int i = 0; i < nfds; i++)
    {
      if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)
        || (!(events[i].events & EPOLLIN)))
      {
        remove_client_from_epoll(epollfd, events[i].data.fd);
        close(events[i].data.fd);
        continue;
      }

      if (events[i].data.fd == sockfd)
      {
        int client_sockfd = process_new_connection(sockfd);
        set_nonblocking(client_sockfd);
        add_client_to_epoll(epollfd, client_sockfd);
      }
      else
      {
        process_exist_connection(events[i].data.fd);
      }
    }
  }

  return 0;
}

