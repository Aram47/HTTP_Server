#include "../../headers/Config/Config.hpp"

using ConfigData = std::unordered_map<std::string, Block* const>;

Config::Config(const ConfigData& servers) : serverVector{servers} {};
