//
// Created by lescalante on 11/11/22.
//

#include <iostream>
#include "LobbyClient.h"
#include "../common/custom_error.h"
#include "../common/lobby_command.h"

LobbyClient::LobbyClient(NonBlockingQueue<std::string> &input_queue, BlockingQueue<std::string> &exit_queue)
: input_queue(input_queue), exit_queue(exit_queue){

}

void LobbyClient::start(std::istream &input) {
    std::cout << "Hello lobby" << std::endl;
    std::string command;
    bool in_game = false;

    while (std::getline(std::cin, command)) {
        exit_queue.push(command);

        bool was_closed = false;

        if (not in_game) {
            LobbyCommand LobbyCommand(input_queue.blocking_pop());

            if (was_closed) {
                throw CustomError("socket was closed by the other end.");
            }

            std::cout << LobbyCommand.serialize() << std::endl;
            in_game = true;
        }
    }
}
