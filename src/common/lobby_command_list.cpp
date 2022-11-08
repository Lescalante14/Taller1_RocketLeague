#include "lobby_command_list.h"
#include <string>
#include <sstream>

#define COMMAND_CODE 0x01

CommandList::CommandList(): Command(COMMAND_CODE) { }

std::string CommandList::run(Lobby* lobby) {
    std::string list(lobby->get_matches_list());
    return list;
}
