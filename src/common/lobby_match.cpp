#include "lobby_match.h"
#include "lobby_match_error.h"
#include <sstream>

LobbyMatch::LobbyMatch(
    const std::string& _name, size_t _players_limit
): name(_name), 
    players(1), 
    players_limit(_players_limit) { }

std::string LobbyMatch::get_description() const {
    std::stringstream description;
    description << this->name 
        << " " << this->players 
        << "/" << this->players_limit;
    return description.str();
}

bool LobbyMatch::add_player() {
    if (this->players >= this->players_limit) {
        throw LobbyMatchError("The match is full.");
    }

    this->players++;

    return this->players == this->players_limit;
}
