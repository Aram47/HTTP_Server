#include <CustomError.hpp>

CustomError::CustomError(const std::string& msg) : message{msg} {};

const char* CustomError::what() const _NOEXCEPT {
	return this->message.c_str();
}
