#ifndef SOCKET_CLOSED_EXCEPTION_H
#define SOCKET_CLOSED_EXCEPTION_H

#include <exception>
#include <string>

class SocketClosedException : public std::exception {
    private:
    std::string msg;

    public:
    SocketClosedException();
    explicit SocketClosedException(std::string _msg);

    virtual const char* what() const noexcept;

    virtual ~SocketClosedException();
};
#endif
