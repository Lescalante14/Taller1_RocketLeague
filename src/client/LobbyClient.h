//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_LOBBYCLIENT_H
#define ROCKET_LEAGUE_LOBBYCLIENT_H


#include <iosfwd>
#include "common/blocking_queue.h"

class LobbyClient {

    BlockingQueue<std::string> &received_queue;
    BlockingQueue<std::string> &to_send_queue;
    const std::string EXIT_COMMAND = "fin";

    void resolveAction(const std::string& action, std::string *command, std::string *payload);
public:

    LobbyClient(BlockingQueue<std::string> &received_queue, BlockingQueue<std::string> &to_send_queue);

    void run(std::istream &input);
};


#endif //ROCKET_LEAGUE_LOBBYCLIENT_H
