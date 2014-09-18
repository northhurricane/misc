#include "enet.h"

#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

typedef unsigned long long uint64;

struct enet_head_struct
{
  uint64 magic;
  int errno;
};
typedef struct enet_head_struct enet_head_t;

#define ENET_MAGIC 0xac32845fb190d762
struct enet_struct
{
  enet_head_t head;
  int handle;
  int hint;
};
typedef enet_struct ENET;

#define ENET_SOCKET_MAGIC 0xb83c96743320cebf
struct enet_socket_struct
{
  enet_head_t head;
  int handle;
  int flags;
};
typedef enet_socket_struct ENET_SOCKET;

#define EPOLLHINT 10

#define ENET_SOCKET_LISTEN 0x0
#define ENET_SOCKET_ACCEPT 0x1

int BACKLOG = 10;

int enet_create(enet_t *enet, int hint)
{
  int epollfd = epoll_create(EPOLLHINT);
  if (epollfd == -1)
    return -1;

  ENET *enet2 = (ENET*) new ENET();
  enet2->head.magic = ENET_MAGIC;
  enet2->handle = epollfd;
  enet2->hint = hint;

  *enet = enet2;

  return 0;
}

int enet_add_socket(enet_t enet, enet_socket_t socket, struct enet_event *event)
{
  struct epoll_event *ev = (struct epoll_event*)event;

  ENET_SOCKET *socket2 = (ENET_SOCKET*)socket;
  ENET *enet2 = (ENET*)enet;

  if (socket2->flags & ENET_SOCKET_ACCEPT)
    ev->events = EPOLLIN | EPOLLET;
  else
    ev->events = EPOLLIN;

  if (epoll_ctl(enet2->handle, EPOLL_CTL_ADD, socket2->handle, ev) == -1)
  {
    return -1;
  }

  return 0;
}

int enet_remove_socket(enet_t enet, enet_socket_t socket)
{
  struct epoll_event event = {0, {0}};

  ENET *enet2 = (ENET*)enet;
  ENET_SOCKET *socket2 = (ENET_SOCKET*)socket;
  
  int r = epoll_ctl(enet2->handle, EPOLL_CTL_DEL, socket2->handle, &event);
  if (r != 0)
    return r;

  return 0;
}

int enet_wait(enet_t enet, struct enet_event *events, int maxevents, int timeout)
{
  return epoll_wait(((ENET*)enet)->handle, (struct epoll_event*)events,
                    maxevents, timeout);
}

int enet_destroy(enet_t enet)
{
  ENET *enet2 = (ENET*)enet;

  int epollfd = enet2->handle;
  delete enet2;

  return close(epollfd);
}

int enet_socket_create(enet_socket_t *socket1, uint16_t port)
{
  ENET_SOCKET *socket2 = new ENET_SOCKET();
  socket2->flags &= ENET_SOCKET_LISTEN;

  int sockfd;
  struct sockaddr_in my_addr;

  if ((sockfd = socket(AF_INET,  SOCK_STREAM,  0)) == -1) 
  {
    return -1;
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(port);
  my_addr.sin_addr.s_addr = INADDR_ANY;

  bzero(&(my_addr.sin_zero), 8);
  if (bind(sockfd,  (struct sockaddr *)&my_addr,  sizeof(struct sockaddr)) == -1) 
  {
    return -1;
  }

  if (listen(sockfd,  BACKLOG) == -1)
  {
    return -1;
  }

  socket2->handle = sockfd;

  *socket1 = (enet_socket_t)socket2;
  return 0;
}

int enet_socket_destroy(enet_socket_t socket)
{
  ENET_SOCKET *socket2 = (ENET_SOCKET*)socket;

  int r = close(socket2->handle);
  delete socket2;

  return r;
}

int enet_socket_accept(enet_socket_t socket, enet_socket_t *accept_socket)
{
  ENET_SOCKET *socket2 = (ENET_SOCKET*)socket;

  struct sockaddr_in remote_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  int client_sockfd;

  client_sockfd = accept(socket2->handle, (struct sockaddr*) &remote_addr, &sin_size);

  if (client_sockfd == -1)
  {
    return -1;
  }

  int opts;

  opts = fcntl(client_sockfd, F_GETFL);
  if (opts < 0)
  {
    return -1;
  }
  opts = opts|O_NONBLOCK;
  if(fcntl(client_sockfd, F_SETFL,opts) < 0)
  {
    return -1;
  }

  ENET_SOCKET *socket3 = new ENET_SOCKET();
  socket3->flags |= ENET_SOCKET_ACCEPT;
  socket3->handle = client_sockfd;

  *acpt_socket = socket3;

  return 0;
}

int enet_socket_recv(enet_socket_t socket, void *buf, int len, int flags)
{
  ENET_SOCKET *socket2 = (ENET_SOCKET*)socket;

  return recv(socket2->handle, buf, len, flags);
}

int enet_socket_send(enet_socket_t socket, const void *buf, int len, int flags)
{
  ENET_SOCKET *socket2 = (ENET_SOCKET*)socket;

  return send(socket2->handle, buf, len, flags);
}

//////////////////////client call//////////////////////
struct enet_client_struct
{
  enet_head_t head;
  int handle;
};
typedef struct enet_client_struct ENET_CLIENT;

int enet_client_create(enet_client_t *client, const char *host, uint16_t port)
{
  int phase = 0;
  int client_socket = -1;

  ENET_CLIENT *client2 = new ENET_CLIENT();
  if (client2 == NULL)
    goto err;

  phase = 1;

  client_socket = socket(AF_INET,SOCK_STREAM,0);
  if( client_socket < 0)
    goto err;

  struct sockaddr_in client_addr;
  bzero(&client_addr,sizeof(client_addr));

  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr(host);
  client_addr.sin_port = htons(port);

  if(client_addr.sin_addr.s_addr == INADDR_NONE)
  {
    struct    hostent        * phost;
    phost = (struct hostent*)gethostbyname(host);
    if(phost==NULL)
      return -1;

    client_addr.sin_addr.s_addr =((struct in_addr*)phost->h_addr)->s_addr;
  }

  if(connect(client_socket,(struct sockaddr*)&client_addr, sizeof(client_addr))<0)
  {
    goto err;
  }

  client2->handle = client_socket;
  *client = client2;

  return 0;

err :
  switch (phase)
  {
    case 2:
      close(client_socket);
    case 1:
      delete client2;
  }
  return -1;
}

int enet_client_send(enet_client_t client, void *buf, int len, int flags)
{
  ENET_CLIENT *client2 = (ENET_CLIENT*)client;

  return send(client2->handle, buf, len, flags);
}

int enet_client_recv(enet_client_t client, void *buf, int len, int flags)
{
  ENET_CLIENT *client2 = (ENET_CLIENT*)client;
  return recv(client2->handle, buf, len, flags);
}

int enet_err()
{
  return 0;
}
