#include "client.h"
#include "../common/socket.h"
#include "../common/protocol.h"
#include "../common/custom_error.h"
#include "../common/lobby_command.h"
#include <string>
#include <iostream>
#include <utility>

void Client::start(
        const char *hostname,
        const char *servname) {
    Socket skt(hostname, servname);

    Protocol protocol(std::move(skt));

    std::string command;

    bool in_game = false;

    while (std::getline(std::cin, command)) {
        protocol.send_message(command);

        bool was_closed = false;

        if (not in_game) {
            LobbyCommand LobbyCommand = protocol.recv_lobby_command(&was_closed);

            if (was_closed) {
                throw CustomError("socket was closed by the other end.");
            }
            
            std::cout << LobbyCommand.serialize() << std::endl;
            in_game = true;
        }
    }
}
