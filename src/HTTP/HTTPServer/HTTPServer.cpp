#include <HTTPServer.hpp>

using middleware = std::function<void(const Streamable&, 
                                      const Streamable&, 
                                      const Next&)>;

HTTPServer::HTTPServer():
  server_address{},
  client_address{},
  server_socket{0},
  client_socket{0},
  __use_table{},
  __get_table{},
  __post_table{},
  __delete_table{},
  __put_table{},
  __patch_table{},
  __head_table{},
  __options_table{}
{}

HTTPServer::~HTTPServer()
{
  close(this->client_socket);
  close(this->server_socket);
}

void HTTPServer::Listen(std::size_t PORT, std::function<void()> cb) {
  if (PORT > 65535) {
    std::cerr << "Invalid PORT" << std::endl;
    return;
  }
	this->PORT = PORT;
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
 	int opt = 1;
	setsockopt(this->server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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
	#ifdef __APPLE__
  	const int BACKLOG = 128;  // macOS may have lower SOMAXCONN
	#else
    const int BACKLOG = SOMAXCONN;
	#endif
  if (listen(this->server_socket, BACKLOG) == -1) {
    std::cerr << "Listening error!" << std::endl;
    return;
  }

  socklen_t client_address_size = sizeof(this->client_address);
  cb();

  this->client_socket = accept(this->server_socket,
                            (sockaddr*)&this->client_address,
                            &client_address_size);

  if (this->client_socket == -1) {
      std::cerr << "Error accepting connection!" << std::endl;
      return;
  }

  // cb();
};

// not finished yet

void HTTPServer::Use(middleware __middleware) {
  for (auto it : this->__get_table) {
    it.second.push_back(__middleware);
  }
  for (auto it : this->__post_table) {
    it.second.push_back(__middleware);
  }
  for (auto it : this->__delete_table) {
    it.second.push_back(__middleware);
  }
  for (auto it : this->__put_table) {
    it.second.push_back(__middleware);
  }
  for (auto it : this->__patch_table) {
    it.second.push_back(__middleware);
  }
  for (auto it : this->__head_table) {
    it.second.push_back(__middleware);
  }
  for (auto it : this->__options_table) {
    it.second.push_back(__middleware);
  }
};

void HTTPServer::Use(const std::vector<middleware>& __middlewares) {
  for (auto middleware : __middlewares) {
    this->Use(middleware);
  }
};

void HTTPServer::Use(const std::string& __path, middleware __middleware) {
  this->__use_table[__path].push_back(__middleware);
};

void HTTPServer::Use(const std::string& __path, 
                     const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->Use(__path, middleware);
  }
};

void HTTPServer::Get(const std::string& __path, 
                     const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->__get_table[__path].push_back(middleware);
  }
};

void HTTPServer::Post(const std::string& __path, 
                      const std::vector<middleware>& __middlewares)
{
  for (auto middleware : __middlewares) {
    this->__post_table[__path].push_back(middleware);
  }
};

void HTTPServer::Delete(const std::string& __path, 
                        const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->__delete_table[__path].push_back(middleware);
  }
};

void HTTPServer::Put(const std::string& __path, 
                     const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->__put_table[__path].push_back(middleware);
  }
};

void HTTPServer::Patch(const std::string& __path, 
                       const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->__patch_table[__path].push_back(middleware);
  }
};

void HTTPServer::Head(const std::string& __path, 
                      const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->__head_table[__path].push_back(middleware);
  }
};

void HTTPServer::Options(const std::string& __path, 
                         const std::vector<middleware>& __middlewares) 
{
  for (auto middleware : __middlewares) {
    this->__options_table[__path].push_back(middleware);
  }
};

// void HTTPServer::HandleRequest() {
//   char buffer[1024] = {0};
//   ssize_t valread = read(this->client_socket, buffer, 1024);
//   if (valread == -1) {
//     std::cerr << "Error reading from socket!" << std::endl;
//     return;
//   }

//   std::string request(buffer);
//   std::string method = request.substr(0, request.find(' '));
//   std::string path = request.substr(request.find(' ') + 1, request.find(' ', request.find(' ') + 1) - request.find(' ') - 1);
//   std::string body = request.substr(request.find("\r\n\r\n") + 4);

//   Streamable req;
//   req.method = method;
//   req.path = path;
//   req.body = body;

//   Streamable res;
//   res.method = method;
//   res.path = path;
//   res.body = body;

//   Next next;
//   next.__use_table = this->__use_table;
//   next.__get_table = this->__get_table;
//   next.__post_table = this->__post_table;
//   next.__delete_table = this->__delete_table;
//   next.__put_table = this->__put_table;
//   next.__patch_table = this->__patch_table;
//   next.__head_table = this->__head_table;
//   next.__options_table = this->__options_table;

//   next.__use_table[path] = this->__use_table[path];
//   next.__get_table[path] = this->__get_table[path];
//   next.__post_table[path] = this->__post_table[path];
//   next.__delete_table[path] = this->__delete_table[path];
//   next.__put_table[path] = this->__put_table[path];
//   next.__patch_table[path] = this->__patch_table[path];
//   next.__head_table[path] = this->__head_table[path];
//   next.__options_table[path] = this->__options_table[path];

//   next.__use_table["/"] = this->__use_table["/"];
//   next.__get_table["/"] = this->__get_table["/"];
//   next.__post_table["/"] = this->__post_table["/"];
//   next.__delete_table["/"] = this->__delete_table["/"];
//   next.__put_table["/"] = this->__put_table["/"];
//   next.__patch_table["/"] = this->__patch_table["/"];
//   next.__head_table
//   ["/"] = this->__head_table["/"];
//   next.__options_table["/"] = this->__options_table["/"];
// };