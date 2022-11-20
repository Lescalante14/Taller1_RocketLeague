#include "client.h"
#include "../common/socket.h"
#include "../common/protocol.h"
#include "../common/custom_error.h"
#include "../common/lobby_command.h"
#include "LobbyClient.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <utility>

void Client::start(
        const char *hostname,
        const char *servname) {

    /*LobbyClient lobby;
    lobby.start(std::cin, hostname, servname);*/
    Game game;
    game.start(std::cin);
}
