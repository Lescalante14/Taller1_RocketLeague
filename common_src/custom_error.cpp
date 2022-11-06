#include "custom_error.h"

#include <utility>

CustomError::CustomError(std::string _msg) : msg(std::move(_msg)) { }

const char* CustomError::what() const noexcept {
    return this->msg.c_str();
}

CustomError::~CustomError() {}
