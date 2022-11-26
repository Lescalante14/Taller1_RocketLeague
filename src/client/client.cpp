#include <string>
#include <iostream>
#include <utility>

#include "client_thread_receiver.h"
#include "client_thread_sender.h"
#include "LobbyClient.h"
#include "client.h"
#include "Game.h"

#include "common/non_blocking_queue.h"
#include "common/blocking_queue.h"
#include "common/lobby_command.h"
#include "common/custom_error.h"
#include "common/protocol.h"
#include "common/socket.h"

void Client::start(
        const char *hostname,
        const char *servname) {
    Socket skt(hostname, servname);
    Protocol protocol(std::move(skt));

    NonBlockingQueue<std::string> input_queue;
    BlockingQueue<std::string> exit_queue;

    ClientThreadReceiver receiver(protocol, input_queue);
    ClientThreadSender sender(protocol, exit_queue);
    receiver.start();
    sender.start();

    LobbyClient lobby(input_queue, exit_queue);
    lobby.start(std::cin);

    Game game(input_queue, exit_queue);
    game.start(std::cin);

    input_queue.close();
    exit_queue.close();
    protocol.closeConnection();
    receiver.join();
    sender.join();
}
