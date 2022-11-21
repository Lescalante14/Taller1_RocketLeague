#include "queue_closed_exception.h"

#include <utility>

QueueClosedException::QueueClosedException(std::string _msg) : msg(std::move(_msg)) { }
QueueClosedException::QueueClosedException(): msg("Queue closed.") {}

const char* QueueClosedException::what() const noexcept {
    return this->msg.c_str();
}

QueueClosedException::~QueueClosedException() {}
