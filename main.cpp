#include <iostream>
#include <HTTPServer.hpp>
#include <header.hpp>

int main(int argc, char** argv) {
  try {
		if (argc > 2) throw CustomError("problem with file");
		Parser pars(argc == 1 ? "default.conf" : argv[1]);
		if (!pars.startParsing()) throw CustomError("Parser Error");
		Config configurations(pars.getResult());

		HTTPServer server;
		const std::size_t PORT = 4568;
		
  	server.Listen(PORT, []() {
    	std::cout << "Server listening on PORT: " << PORT << std::endl;
  	});

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::exit(1);
	}
}
