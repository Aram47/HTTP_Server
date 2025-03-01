#ifndef __HTTP_SERVER__
#define __HTTP_SERVER__

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <functional>

#ifdef __linux__
#include <bits/c++config.h>
#endif

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

class HTTPServer {
public:
  /*
    constructors and destructor
  */
  HTTPServer(const HTTPServer&) = delete;
  HTTPServer(HTTPServer&&) = delete;
  HTTPServer();
  ~HTTPServer();
public:
  /*
    public methods for working with HTTPServer
  */
  void Listen(std::size_t, std::function<void()>);
private:
  std::size_t PORT;
  int server_socket;
  int client_socket;
  /*
    sockaddr_in = a Struct that stores address and port information
  */
  sockaddr_in server_address;
  sockaddr_in client_address;
};

#endif
