#ifndef LOBBY_COMMAND_LIST_H
#define LOBBY_COMMAND_LIST_H

#include "lobby_command.h"
#include <string>

/*
 * Comando para listar las partidas del lobby deseado
 * */
class CommandList: public Command {
public:
    CommandList();
    std::string run(Lobby* lobby) override;
};
#endif

