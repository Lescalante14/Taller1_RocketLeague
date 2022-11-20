#ifndef QUEUE_EMPTY_EXCEPTION_H
#define QUEUE_EMPTY_EXCEPTION_H

#include <exception>
#include <string>

class QueueEmptyException : public std::exception {
    private:
    std::string msg;

    public:
    QueueEmptyException();
    explicit QueueEmptyException(std::string _msg);

    virtual const char* what() const noexcept;

    virtual ~QueueEmptyException();
};
#endif
