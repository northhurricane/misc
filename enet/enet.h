#ifndef ENET_H_
#define ENET_H_

#include <stdint.h>

typedef void* enet_t;
typedef void* enet_socket_t;

typedef union enet_data
{
  void     *ptr;
  int      fd;
  uint32_t u32;
  uint64_t u64;
} enet_data_t;

struct enet_event
{
  uint32_t    events;
  enet_data_t data;
} __attribute__ ((__packed__));

int enet_create(enet_t *enet, int hint);
int enet_add_socket(enet_t enet, enet_socket_t socket, struct enet_event *event);
int enet_remove_socket(enet_t enet, enet_socket_t socket);
int enet_wait(enet_t enet, struct enet_event *events, int maxevents, int timeout);
int enet_destroy(enet_t enet);

int enet_socket_create(enet_socket_t *socket, uint16_t port);
int enet_socket_destroy(enet_socket_t socket);
int enet_socket_accept(enet_socket_t socket, enet_socket_t *accept_socket);

int enet_client_create(enet_socket_t *socket, const char *host, uint16_t port);
int enet_client_destroy(enet_socket_t socket);

int enet_socket_recv(enet_socket_t socket, void *buf, int len, int flags);
int enet_socket_send(enet_socket_t socket, const void *buf, int len, int flags);

#endif //_ENET_H
