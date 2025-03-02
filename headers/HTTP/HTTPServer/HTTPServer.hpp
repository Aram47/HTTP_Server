#ifndef __HTTP_SERVER__
#define __HTTP_SERVER__

#include <iostream>
#include <unordered_map>
#include <vector>
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

#include <Streamable.hpp>
#include <Next.hpp>

class HTTPServer {
using middleware = std::function<void(const Streamable&, 
                                      const Streamable&, 
                                      const Next&)>;
using table = std::unordered_map<std::string, std::vector<middleware>>;

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

  void Use(middleware);
  void Use(const std::vector<middleware>&);
  void Use(const std::string&, middleware);
  void Use(const std::string&, const std::vector<middleware>&);
  
  void Get(const std::string&, const std::vector<middleware>&);
  void Post(const std::string&, const std::vector<middleware>&);
  void Delete(const std::string&, const std::vector<middleware>&);
  void Put(const std::string&, const std::vector<middleware>&);
  void Patch(const std::string&, const std::vector<middleware>&);
  void Head(const std::string&, const std::vector<middleware>&);
  void Options(const std::string&, const std::vector<middleware>&);

private:
  /*
    sockaddr_in = a Struct that stores address and port information
  */
  sockaddr_in server_address;
  sockaddr_in client_address;
  int server_socket;
  int client_socket;
  std::size_t PORT;
  table __use_table;
  table __get_table;
  table __post_table;
  table __delete_table;
  table __put_table;
  table __patch_table;
  table __head_table;
  table __options_table;
};

#endif // __HTTP_SERVER__
