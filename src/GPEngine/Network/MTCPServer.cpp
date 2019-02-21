#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "MTCPServer.h"

MTCPServer::MTCPServer() {
  server_socket = NULL;
  socket_set = NULL;
  sockets = NULL;
  num_sockets = 0;
  max_sockets = 0;
  num_cores = 1;
  port = 0;
}

MTCPServer::~MTCPServer() {
  if(socket_set != NULL) {
    for(int i = 0; i < num_sockets; i++) {
      if(SDLNet_TCP_DelSocket(socket_set, sockets[i]) == -1) {
        printf("SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
        exit(-1);
      } else {
        SDLNet_TCP_Close(sockets[i]);
        sockets[i] = NULL;
      }
    }
    if(SDLNet_TCP_DelSocket(socket_set, server_socket) == -1) {
      printf("SDLNet_TCP_DelSocket: %s\n", SDLNet_GetError());
      exit(-1);
    } else {
      SDLNet_TCP_Close(server_socket);
      server_socket = NULL;
      SDLNet_FreeSocketSet(socket_set);
      socket_set = NULL;
    }
  }
  if(sockets != NULL) delete[] sockets;
  num_sockets = 0;
  port = 0;
}

void MTCPServer::setNumClients(int n) {
  if(n <= 0) {
    printf("Warning: NumClients set to %d\n", n);
    max_sockets = 0;
  } else {
    max_sockets = n;
  }
}

void MTCPServer::setNumCores(int n) {
  if(n <= 1) {
    printf("Warning: NumCores set to %d\n", n);
    num_cores = 1;
  } else {
    num_cores = n;
  }
}

void MTCPServer::start(Uint16 p) {
  IPaddress ip;
  if(SDLNet_ResolveHost(&ip, NULL, p) == -1) {
    printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    exit(-1);
  }
  server_socket = SDLNet_TCP_Open(&ip);
  if(server_socket == NULL) {
    printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    exit(-1);
  }
  socket_set = SDLNet_AllocSocketSet(max_sockets+1);
  if(SDLNet_TCP_AddSocket(socket_set, server_socket) == -1) {
    printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
    exit(-1);
  }
  sockets = new TCPsocket[max_sockets];
  port = p;
  num_sockets = 0;
}






















