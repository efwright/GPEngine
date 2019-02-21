#ifndef MSERVER_HEADER
#define MSERVER_HEADER

MTCPSocket* M_createTCPSocket(Uint16 port) {
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
    socket->port = port;
  }
}

#endif

