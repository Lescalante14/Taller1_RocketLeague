#ifndef LOBBY_COMMAND_ERROR_H
#define LOBBY_COMMAND_ERROR_H

#include <exception>
#include <string>

class CommandError : public std::exception {
    private:
    std::string msg;

    public:
    explicit CommandError(std::string _msg);

    virtual const char* what() const noexcept;

    virtual ~CommandError();
};
#endif
