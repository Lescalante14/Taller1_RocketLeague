#include "client.h"
#include "../common/socket.h"
#include "../common/protocol.h"
#include "../common/custom_error.h"
#include "../common/lobby_command.h"
#include "LobbyClient.h"
#include "Game.h"
#include "../common/non_blocking_queue.h"
#include "../common/blocking_queue.h"
#include "thread_sender.h"
#include "thread_receiver.h"
#include <string>
#include <iostream>
#include <utility>

void Client::start(
        const char *hostname,
        const char *servname) {
    Socket skt(hostname, servname);
    Protocol protocol(std::move(skt));
    NonBlockingQueue<std::string> input_queue;
    BlockingQueue<std::string> exit_queue;

    ThreadReceiver receiver(protocol, input_queue);
    ThreadSender sender(protocol, exit_queue);
    receiver.start();
    sender.start();


    std::string command;
    bool in_game = false;

    /*LobbyClient lobby;
    lobby.start(std::cin, hostname, servname);*/
    Game game;
    game.start(std::cin);
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


    receiver.join();
    sender.join();
}
