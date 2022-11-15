#include "lobby_command_join.h"
#include <string>
#include <iostream>
#include <sstream>

#define COMMAND_CODE 0x02

CommandJoin::CommandJoin(const std::string& payload)
    : Command(COMMAND_CODE), match_name(payload) { }

std::string CommandJoin::run(Lobby* lobby) {
    lobby->add_player_to_match(this->match_name);
    return "";
}
