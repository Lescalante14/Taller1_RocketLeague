//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTROCKETLEAGUE_H
#define ROCKET_LEAGUE_CLIENTROCKETLEAGUE_H


#include <istream>
#include "../common/protocol.h"
#include "Game.h"
#include "LobbyClient.h"

class ClientRocketLeague {
private:
    //Protocol protocol;
    LobbyClient lobby;
    Game game;
public:
    ClientRocketLeague() = default;
    ClientRocketLeague(const char *hostname, const char *servName);
    void start(std::istream &input);
};


#endif //ROCKET_LEAGUE_CLIENTROCKETLEAGUE_H
