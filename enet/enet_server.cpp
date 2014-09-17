#include "enet.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define PORT 5966

void process_communicate(enet_socket_t socket);

int main()
{
  cout << "enter enet server" << endl;

  int r;

  enet_socket_t socket;
  r = enet_socket_create(&socket, PORT);

  enet_t enet;
  r = enet_create(&enet, 10);
  cout << "create enet" << endl;

  struct enet_event event;
  event.data.ptr = socket;
  r = enet_add_socket(enet, socket, &event);

#define MAXEVENTS 10
  struct enet_event events[MAXEVENTS];
  enet_socket_t acpt_socket;
  int r2;
  while (true)
  {
    r = enet_wait(enet, events, MAXEVENTS, -1);
    for (int i = 0; i < r; i++)
    {
      if (events[i].data.ptr == socket)
      {
        //accept new connection
        r2 = enet_socket_accept(socket, &acpt_socket);
        event.data.ptr = acpt_socket;
        r2 = enet_add_socket(enet, acpt_socket, &event);
      }
      else
      {
        process_communicate(events[i].data.ptr);
      }
    }
  }

  return 0;
}

void process_communicate(enet_socket_t socket)
{
  char recv_buf[100];
  char send_buf[200];
  int r;

  r = enet_socket_recv(socket, recv_buf, sizeof(recv_buf), 0);
  recv_buf[r] = 0;

  cout << "recieved message : " << recv_buf << endl;
  sprintf(send_buf, "server recieved what you said '%s'", recv_buf);

  r = enet_socket_send(socket, send_buf, strlen(send_buf), 0);
}
