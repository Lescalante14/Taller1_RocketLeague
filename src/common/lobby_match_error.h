#ifndef LOBBY_MATCH_ERROR_H
#define LOBBY_MATCH_ERROR_H

#include <exception>
#include <string>

class LobbyMatchError : public std::exception {
    private:
    std::string msg;

    public:
    explicit LobbyMatchError(std::string _msg);

    virtual const char* what() const noexcept;

    virtual ~LobbyMatchError();
};
#endif
