#ifndef __PARSER__
#define __PARSER__

#include <unordered_map>
#include <vector>
#include <string>
#include <Block.hpp>

class Parser {
using Tokens = std::vector<std::string>;
using ConfigData = std::unordered_map<std::string, Block* const>;
public:
	Parser(const std::string&);
public:
	const ConfigData getResult() const;
	/*
		will use instace of FileHandler class for checking is
		valid file or not and handle working with him

		FileHandler can throw exception if something will be wrong
	*/
	bool startParsing();
private:
	/*
		step 1
		lexical analyse

		will return std::vector<std::string>
		for example`

		input`
			server {
				listen 8002;
					server_name localhost;
			}
		otput`
			Tokens = ["server", "{", "listen", "8002", ";", "server_name", "localhost", ";", "}"]
	*/
	const Tokens tokeniser() const;
	/*
		step 2

		check syntax
	*/
	/*
		using Tokens = std::vector<std::string>;
		using ConfigData = std::unordered_map<std::string, Block* const>;
	*/
	bool syntaxChecker() const;
private:
	Parser& operator=(const Parser&) {return *this;};
private:
	ConfigData endlyResult;
};

#endif // __PARSER__
