#ifndef MTCPSERVER_HEADER
#define MTCPSERVER_HEADER

class MTCPServer {
  public:
    MTCPServer();
    ~MTCPServer();
    TCPsocket server_socket;
    SDLNet_SocketSet socket_set;
    TCPsocket *sockets;
    Uint16 port;
    int num_cores;
    int max_sockets;
    int num_sockets;

    void setNumClients(int);
    void setNumCores(int);
    void start(Uint16);
};

#endif

