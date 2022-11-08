#include "lobby_command_create.h"
#include <sstream>
#include <iostream>
#include <string>

#define COMMAND_CODE 0x01

CommandCreate::CommandCreate(std::string payload)
    : Command(COMMAND_CODE), players_limit(0) {
    std::stringstream ss(payload);
    ss >> this->players_limit;
    std::string rem;
    std::getline(ss, rem);
    this->match_name = rem.substr(1);
}

std::string CommandCreate::run(Lobby* lobby) {
    lobby->create_match(this->match_name, this->players_limit);
    return "";
}
