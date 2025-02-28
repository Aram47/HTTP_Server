#ifndef __HTTP_SERVER__
#define __HTTP_SERVER__

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <bits/c++config.h>
#include <functional>

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