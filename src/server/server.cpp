#include "server.h"
#include "../common/socket.h"
#include "thread_matchs_handler.h"
#include "thread_acceptor.h"
#include "../common/thread.h"
#include "../common/lobby.h"
#include <string>
#include <iostream>

void Server::start(const char *servname) { 
    Socket skt(servname);
    BlockingQueue<LobbyMatch*> matchs_to_start;
    Lobby lobby(matchs_to_start);

    ThreadMatchsHandler matchs_handler(matchs_to_start);
    matchs_handler.start();

    bool keep_accepting(true);
    ThreadAcceptor acceptor(&skt, lobby, &keep_accepting);

    acceptor.start();

    std::string input;
    while (std::getline(std::cin, input)) {
        if (input == "q") break;
    }

    keep_accepting = false;
    skt.shutdown(2);
    skt.close();
    matchs_to_start.close();
    matchs_handler.join();
    acceptor.join();
}
