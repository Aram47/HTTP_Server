#include <iostream>
#include "./headers/HTTPServer/HTTPServer.hpp"

int main(void) {
  HTTPServer server;
  server.Listen(4568, []() {
    std::cout << "Hello World!!!" << std::endl;
  });
}