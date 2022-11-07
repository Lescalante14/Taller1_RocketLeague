#ifndef LOBBY_COMMAND_JOIN_H
#define LOBBY_COMMAND_JOIN_H

#include "lobby_command.h"
#include <string>

/*
 * Comando para unir un nuevo jugador a una
 * partida en el lobby deseado
 * */
class CommandJoin: public Command {
private:
    std::string match_name;

public:
    explicit CommandJoin(const std::string& payload);
    std::string run(Lobby* lobby) override;
};
#endif

