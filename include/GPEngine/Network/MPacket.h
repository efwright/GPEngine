#ifndef MPACKET_HEADER
#define MPACKET_HEADER

#include <SDL2/SDL_net.h>

#define DEFAULT_PACKET_SIZE 0xFF
#define DEFAULT_PACKET_VECTOR_LENGTH 0x01

/**
 *  Wrapper class for SDL2 UDPpacket
 */

class MPacket {
  public:
    MPacket();
    ~MPacket();
    UDPpacket *packet;
    unsigned int size;
};

MPacket* M_createPacket();
MPacket* M_createPacket(unsigned int);
void M_destroyPacket(MPacket*);

class MPacketVector {
  public:
    MPacketVector();
    ~MPacketVector();
    UDPpacket **packets;
    unsigned int size;
    unsigned int numPackets;
};

MPacketVector* M_createPacketVector();
MPacketVector* M_createPacketVector(unsigned int);
MPacketVector* M_createPacketVector(unsigned int, unsigned int);
void M_destroyPacketVector(MPacketVector*);

#endif

