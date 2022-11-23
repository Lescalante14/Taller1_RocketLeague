//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_LOBBYCLIENT_H
#define ROCKET_LEAGUE_LOBBYCLIENT_H


#include <iosfwd>
#include "common/non_blocking_queue.h"
#include "common/blocking_queue.h"

class LobbyClient {

    NonBlockingQueue<std::string> &input_queue;
    BlockingQueue<std::string> &exit_queue;
public:
    LobbyClient(NonBlockingQueue<std::string> &input_queue, BlockingQueue<std::string> &exit_queue);

    void start(std::istream &input);
};


#endif //ROCKET_LEAGUE_LOBBYCLIENT_H
