#include "../../headers/HTTPServer/HTTPServer.hpp"

HTTPServer::HTTPServer(): 
  server_socket{0},
  client_socket{0},
  server_address{},
  client_address{}
{}

HTTPServer::~HTTPServer() {
  close(this->client_socket);
  close(this->server_socket);
}

void HTTPServer::Listen(std::size_t PORT, std::function<void()> cb) {
  if (PORT > 65535) {
    std::cerr << "Invalid PORT" << std::endl;
    return;
  }
  /*
    AF_INET       = using IPv4
    SOCK_STREAM   = using TCP protocol
    0             = default protocol for using TCP

    if function socket will be return -1 it's meen
    we have an error
  */
  this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->server_socket == -1) {
    std::cerr << "Error creating socket!" << std::endl;
    return;
  }

  // 
  /*
    AF_INET = We use IPv4;
    htons(PORT) = converts a port from host format (regular number) to 
                  network format (big-endian)
    INADDR_ANY = means that the server will accept connections to 
                  all available IP addresses.
  */
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_port = htons(PORT);
  this->server_address.sin_addr.s_addr = INADDR_ANY;

  if (bind(this->server_socket, 
           (sockaddr*)&this->server_address, 
           sizeof(this->server_address)) == -1) 
  {
    std::cerr << "Error binding socket!" << std::endl;
    return;
  }

  /*
    SOMAXCONN = the maximum number of pending connections in the queue.
    SOMAXCONN = 4096
  */

  if (listen(this->server_socket, SOMAXCONN) == -1) {
    std::cerr << "Listening error!" << std::endl;
    return;
  }

  socklen_t client_address_size = sizeof(this->client_address);

  this->client_socket = accept(this->server_socket, 
                            (sockaddr*)&this->client_address, 
                            &client_address_size);
  
  if (this->client_socket == -1) {
      std::cerr << "Error accepting connection!" << std::endl;
      return;
  }

  cb();
}