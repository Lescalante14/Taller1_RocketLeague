#ifndef QUEUE_CLOSED_EXCEPTION_H
#define QUEUE_CLOSED_EXCEPTION_H

#include <exception>
#include <string>

class QueueClosedException : public std::exception {
    private:
    std::string msg;

    public:
    QueueClosedException();
    explicit QueueClosedException(std::string _msg);

    virtual const char* what() const noexcept;

    virtual ~QueueClosedException();
};
#endif
