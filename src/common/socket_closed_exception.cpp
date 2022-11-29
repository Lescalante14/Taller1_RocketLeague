#include "socket_closed_exception.h"

#include <utility>

SocketClosedException::SocketClosedException(std::string _msg) : msg(std::move(_msg)) { }
SocketClosedException::SocketClosedException(): msg("Socket was closed by the other end..") {}

const char* SocketClosedException::what() const noexcept {
    return this->msg.c_str();
}

SocketClosedException::~SocketClosedException() {}
