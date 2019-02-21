#ifndef MTCPSOCKET_HEADER
#define MTCPSOCKET_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "MPacket.h"

class MTCPSocket {
  public:
    MTCPSocket();
    ~MTCPSocket();
    TCPsocket socket;
    SDLNet_SocketSet set;
    Uint16 port;
    bool ready();
    bool send(char*, int);
    bool recv();
};

MTCPSocket* M_createClientTCPSocket(std::string, Uint16);
MTCPSocket* M_createHostTCPSocket(Uint16);
MTCPSocket* M_closeTCPSocket();

#endif

