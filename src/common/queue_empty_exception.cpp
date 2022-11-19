#include "queue_empty_exception.h"

#include <utility>

QueueEmptyException::QueueEmptyException(std::string _msg) : msg(std::move(_msg)) { }
QueueEmptyException::QueueEmptyException(): msg("Queue empty.") {}

const char* QueueEmptyException::what() const noexcept {
    return this->msg.c_str();
}

QueueEmptyException::~QueueEmptyException() {}
