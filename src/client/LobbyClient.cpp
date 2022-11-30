//
// Created by lescalante on 11/11/22.
//

#include <iostream>

#include "LobbyClient.h"
#include "common/custom_error.h"
#include "common/lobby_command.h"

LobbyClient::LobbyClient(NonBlockingQueue<std::string> &received_queue, BlockingQueue<std::string> &to_send_queue)
: received_queue(received_queue), to_send_queue(to_send_queue){

}

void LobbyClient::run(std::istream &input) {
    std::cout << "Hello lobby" << std::endl;
    std::string line;
    bool in_lobby = true;

    while (in_lobby && std::getline(std::cin, line)) {
        std::string command;
        std::string payload;
        if (line == EXIT_COMMAND) {
            in_lobby = false;
        } else {
            resolveAction(line, &command, &payload);
            auto code = command == "listar" ? LIST_CODE
                    : command == "crear" ? CREATE_CODE
                    : command == "unir" ? JOIN_CODE : -1;
            if (code == -1) {
                std::cout << "Invalid Command" << std::endl;
                continue;
            }
            LobbyCommand lobbyCommand(code, payload);
            std::string commandSer = lobbyCommand.serialize();
            to_send_queue.push(commandSer);
            LobbyCommand response(received_queue.blocking_pop());
            std::cout << response.serialize() << std::endl;
            // creacion o union correcta
            if ((code == CREATE_CODE || code == JOIN_CODE) && response.get_code() == 0) {
                in_lobby = false;
            }
        }
    }
}

void LobbyClient::resolveAction(const std::string& action, std::string *command, std::string *payload) {
    //TODO: trimRight with replace ' \n','\n'
    size_t n = action.find(' ');
    if (n == std::string::npos) {
        *command = action;
    } else {
        *command = action.substr(0, n);
        *payload = action.substr(n+1);
    }
}
