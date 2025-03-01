#include <Parser.hpp>

using Tokens = std::vector<std::string>;
using ConfigData = std::unordered_map<std::string, Block* const>;

Parser::Parser(const std::string&) {

}

const ConfigData Parser::getResult() const {
	return {
		{"a", new Block()}
	};
}

bool Parser::startParsing() {
	return true;
}

const Tokens Parser::tokeniser() const {
	return {"a", "b"};
}

bool Parser::syntaxChecker() const {
	return true;
}
