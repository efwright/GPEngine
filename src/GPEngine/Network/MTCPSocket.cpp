#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "MPacket.h"

#include "MTCPSocket.h"

MTCPSocket::MTCPSocket() {
  socket = NULL;
  port = 0;
}

MTCPSocket::~MTCPSocket() {
  if(socket != NULL) {
    SDLNet_TCP_DelSocket(set, socket);
    SDLNet_FreeSocketSet(set);
    SDLNet_TCP_Close(socket);
    socket = NULL;
  }
  port = 0;
}

MTCPSocket* M_createClientTCPSocket(std::string ip, Uint16 port) {
  MTCPSocket *socket = new MTCPSocket();
  IPaddress SDL_IP;
  if(SDLNet_ResolveHost(&SDL_IP, ip.c_str(), port) == -1) {
    printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    exit(-1);
  }

  socket->socket = SDLNet_TCP_Open(&SDL_IP);
  if(socket->socket == NULL) {
    printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    exit(-1);
  } else {
    socket->set = SDLNet_AllocSocketSet(1);
    if(SDLNet_TCP_AddSocket(socket->set, socket->socket) == -1) {
      printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
      exit(-1);
    } else {
      socket->port = port;
    }
  }
}

MTCPSocket* M_createHostTCPSocket(Uint16 port) {
  MTCPSocket *socket = new MTCPSocket();
  IPaddress SDL_IP;
  if(SDLNet_ResolveHost(&SDL_IP, NULL, port) == -1) {
    printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    exit(-1);
  }

  socket->socket = SDLNet_TCP_Open(&SDL_IP);
  if(socket->socket == NULL) {
    printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    exit(-1);
  } else {
    socket->set = SDLNet_AllocSocketSet(1);
    if(SDLNet_TCP_AddSocket(socket->set, socket->socket) == -1) {
      printf("SDLNet_TCP_AddSocket: %s\n", SDLNet_GetError());
      exit(-1);
    } else {
      socket->port = port;
    }
  }
}

void M_closeTCPSocket(MTCPSocket* socket) {
  delete socket;
}

bool MTCPSocket::ready() {
  bool rd = false;
  int numready = SDLNet_CheckSockets(set, 0);
  if(numready == -1) {
    printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
  } else {
    if(numready) rd = SDLNet_SocketReady(socket);
  }
  return rd;
}

bool MTCPSocket::send(char *msg, int len) {
  int result;
  result = SDLNet_TCP_Send(socket, msg, len+1);
  if(result != len+1) {
    printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
    return false;
  } else {
    return true;
  }
}

bool MTCPSocket::recv() {

}

