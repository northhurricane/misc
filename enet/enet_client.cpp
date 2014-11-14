#include "enet.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

#define HOST "127.0.0.1"
#define PORT 5966

using namespace std;
int main()
{
  int r;
  enet_socket_t socket;

  r = enet_client_create(&socket, HOST, PORT);
  if (r < 0)
  {
    cout << "unable to connect to server" << endl;
    exit(1);
  }
  char buf[100];

  cout << "what you want to say to server?" << endl;

  cin >> buf;
  r = enet_client_send(socket, buf, strlen(buf), 0);
  if (r < 0)
  {
  }

  r = enet_client_recv(socket, buf, sizeof(buf), 0);
  buf[r] = 0;

  cout << buf << endl;

  return 0;
}
