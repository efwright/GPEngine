#ifndef MUDPSOCKET_HEADER
#define MUDPSOCKET_HEADER

#define DEFAULT_UDP_PORT 1337

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "MPacket.h"

class MUDPSocket {
  public:
    MUDPSocket();
    ~MUDPSocket();
    UDPsocket socket;
    Uint16 port;
    int bind(std::string, Uint16, int);
    int unbind(int);
    int send(int, MPacket*);
    bool recv(MPacket*);
    int sendV(int, MPacketVector*);
    bool recvV(MPacketVector*);
};

MUDPSocket * M_openUDPSocket(Uint16);
MUDPSocket * M_openUDPSocket();
void M_closeUDPSocket(MUDPSocket*);
int getNumUDPChannels();
int getNumUDPAddresses();

#endif

