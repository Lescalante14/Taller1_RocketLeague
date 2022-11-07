#include "lobby_match_error.h"

#include <utility>

LobbyMatchError::LobbyMatchError(std::string _msg) : msg(std::move(_msg)) { }

const char* LobbyMatchError::what() const noexcept {
    return this->msg.c_str();
}

LobbyMatchError::~LobbyMatchError() {}
