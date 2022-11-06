#include "lobby_command_error.h"

#include <utility>

CommandError::CommandError(std::string _msg) : msg(std::move(_msg)) { }

const char* CommandError::what() const noexcept {
    return this->msg.c_str();
}

CommandError::~CommandError() {}
