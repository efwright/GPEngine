#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "MPacket.h"
#include "MUDPSocket.h"

MUDPSocket::MUDPSocket() {
  socket = NULL;
  port = 0;
}

MUDPSocket::~MUDPSocket() {
  if(socket != NULL) {
    SDLNet_UDP_Close(socket);
    socket = NULL;
  }
  port = 0;
}

MUDPSocket * M_openUDPSocket(Uint16 port) {
  MUDPSocket * socket = new MUDPSocket();
  socket->socket = SDLNet_UDP_Open(port);
  if(socket->socket == NULL) {
    printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    exit(-1);
  } else {
    socket->port = port;
    return socket;
  }
}

MUDPSocket * M_openUDPSocket() {
  return M_openUDPSocket(DEFAULT_UDP_PORT);
}

void M_closeUDPSocket(MUDPSocket* socket) {
  delete socket;
}

int MUDPSocket::bind(std::string ip, Uint16 port, 
              int channel)
{
  IPaddress SDL_IP;
  SDLNet_ResolveHost(&SDL_IP, ip.c_str(), port);
  int rchannel;
  rchannel = SDLNet_UDP_Bind(socket, channel, &SDL_IP);
  if(rchannel == -1) {
    printf("SDL_Net_UDP_Bind: %s\n", SDLNet_GetError());
    exit(-1);
  } else {
    return rchannel;
  }
}

int MUDPSocket::unbind(int channel) {
  SDLNet_UDP_Unbind(socket, channel);
}

int MUDPSocket::send(int channel, MPacket* packet) {
  int numsent;
  numsent = SDLNet_UDP_Send(socket, channel, packet->packet);
  if(numsent == 0) {
    printf("SDLNet_UDP_Send error (no recipient?): %s\n", SDLNet_GetError());
  }
  return numsent;
}

bool MUDPSocket::recv(MPacket* packet) {
  int numrecv;
  numrecv = SDLNet_UDP_Recv(socket, packet->packet);
  if(numrecv < 0) {
    printf("SDLNet_UDP_Recv: %s\n", SDLNet_GetError());
    exit(-1);
  }
  return numrecv != 0;
}

int MUDPSocket::sendV(int channel, MPacketVector* pVector) {
  int numsent;
  numsent = SDLNet_UDP_SendV(socket, pVector->packets, pVector->numPackets);
  if(numsent == 0) {
    printf("SDLNet_UDP_SendV: %s\n", SDLNet_GetError());
  }
  return numsent;
}

bool MUDPSocket::recvV(MPacketVector* pVector) {
  int numrecv;
  numrecv = SDLNet_UDP_RecvV(socket, pVector->packets);
  if(numrecv < 0) {
    printf("SDLNet_UDP_RecvV: %s\n", SDLNet_GetError());
    exit(-1);
  }
  return numrecv != 0;
}

int getNumUDPChannels() {
  return SDLNET_MAX_UDPCHANNELS;
}

int getNumUDPAddresses() {
  return SDLNET_MAX_UDPADDRESSES;
}

