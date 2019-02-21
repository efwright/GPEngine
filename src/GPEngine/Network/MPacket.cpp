#include <SDL2/SDL_net.h>

#include "MPacket.h"

// MPACKET ////////////////////////////////////////////////////

MPacket::MPacket() {
  packet=NULL;
  size=0;
}

MPacket::~MPacket() {
  if(packet != NULL) {
    SDLNet_FreePacket(packet);
    packet=NULL;
  }
  size=0;
}

MPacket* M_createPacket(unsigned int size) {
  MPacket *packet = new MPacket();
  packet->packet = SDLNet_AllocPacket(size);
  if(packet->packet == NULL) {
    printf("SDLNet_AllocPacket: %s\n", SDLNet_GetError());
    exit(-1);
  } else {
    packet->size = size;
    return packet;
  }
}

MPacket* M_createPacket() {
  return M_createPacket(DEFAULT_PACKET_SIZE);
}

void M_destroyPacket(MPacket* packet) {
  delete packet;
}


// MPACKETVECTOR //////////////////////////////////////////////

MPacketVector::MPacketVector() {
  packets = NULL;
  size = 0;
  numPackets = 0;
}

MPacketVector::~MPacketVector() {
  if(packets != NULL) {
    SDLNet_FreePacketV(packets);
    packets = NULL;
  }
  size = 0;
  numPackets = 0;
}

MPacketVector* M_createPacketVector(unsigned int numPackets, unsigned int packetSize) {
  MPacketVector *pVector = new MPacketVector();
  pVector->packets=SDLNet_AllocPacketV(numPackets, packetSize);
  if(pVector->packets == NULL) {
    printf("SDLNet_AllocPacketV: %s\n", SDLNet_GetError());
    exit(-1);
  } else {
    pVector->size = packetSize;
    pVector->numPackets = numPackets;
    return pVector;
  }
}

MPacketVector* M_createPacketVector() {
  return M_createPacketVector(DEFAULT_PACKET_VECTOR_LENGTH,
                              DEFAULT_PACKET_SIZE);
}

MPacketVector* M_createPacketVector(unsigned int numPackets) {
  return M_createPacketVector(numPackets,
                              DEFAULT_PACKET_SIZE);
}

void M_destroyPacketVector(MPacketVector* pVector) {
  delete pVector;
}

