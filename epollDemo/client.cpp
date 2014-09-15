#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

#define host "127.0.0.1"
#define port 9527

using namespace std;

int main()
{
  int client_socket = socket(AF_INET,SOCK_STREAM,0);
  if( client_socket < 0)
  {
    printf("Create Socket Failed!\n");
    exit(1);
  }

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
    {
      perror("Init socket s_addr error!");
      exit(1);
    }
    client_addr.sin_addr.s_addr =((struct in_addr*)phost->h_addr)->s_addr;
  }

  if(connect(client_socket,(struct sockaddr*)&client_addr, sizeof(client_addr))<0)
  {
    perror("Connect server fail!");
    exit(1);
  }

  char send_buf[200];
  char recv_buf[250];

  cout << "what you want to say to server?" << endl;
  cin >> send_buf;

  int send_len = 0;
  if((send_len = send(client_socket, send_buf, strlen(send_buf), 0)) <= 0)
  {
    perror("send error");
    exit(1);
  }

  int recv_len;
  recv_len = recv(client_socket, recv_buf, sizeof(recv_buf), 0);
  recv_buf[recv_len] = 0;
  cout << "server response : " << recv_buf << endl;

  close(client_socket);

  return 0;
}
