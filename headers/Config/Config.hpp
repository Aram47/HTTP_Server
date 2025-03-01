#ifndef __CONFIG__
#define __CONFIG__

#include <unordered_map>
#include <string>
#include <Block.hpp>

class Config {
using ConfigData = std::unordered_map<std::string, Block* const>;
public:
	Config(const ConfigData& servers);
private:
	Config& operator=(const Config&) { return *this; };
private:
	ConfigData serverVector;
};

#endif
