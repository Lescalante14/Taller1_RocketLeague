#include <string>
#include <iostream>
#include <utility>

#include "client_thread_receiver.h"
#include "client_thread_sender.h"
#include "LobbyClient.h"
#include "client.h"
#include "Game.h"

#include "common/blocking_queue.h"
#include "common/lobby_command.h"
#include "common/custom_error.h"
#include "common/protocol.h"
#include "common/socket.h"

void Client::run(
        const char *hostname,
        const char *servname) {
    Socket skt(hostname, servname);
    Protocol protocol(skt);

    BlockingQueue<std::string> received_queue;
    BlockingQueue<std::string> to_send_queue;

    ClientThreadReceiver receiver(protocol, received_queue);
    ClientThreadSender sender(protocol, to_send_queue);
    receiver.start();
    sender.start();

    LobbyClient lobby(received_queue, to_send_queue);
    lobby.run(std::cin);

    Game game(received_queue, to_send_queue);
    game.run();

    received_queue.close();
    to_send_queue.close();
    protocol.closeConnection();
    receiver.join();
    sender.join();
}
