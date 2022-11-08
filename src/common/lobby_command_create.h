#ifndef LOBBY_COMMAND_CREATE_H
#define LOBBY_COMMAND_CREATE_H

#include "lobby_command.h"
#include <string>

/*
 * Comando para crear una nueva partida en el lobby
 * deseado
 * */
class CommandCreate: public Command {
private:
    std::string match_name;
    size_t players_limit;

public:
    explicit CommandCreate(std::string payload);
    std::string run(Lobby* lobby) override;
};
#endif
