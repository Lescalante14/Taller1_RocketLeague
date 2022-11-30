//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H


#include <istream>

#include "client/helpers/MockProvider.h"
#include "client/presentation/ClientMatch.h"
#include "common/blocking_queue.h"

class Game {

private:
    BlockingQueue<std::string> &received_queue;
    BlockingQueue<std::string> &to_send_queue;

    std::string popGameState(std::string actualState, bool *running);
public:
    Game(BlockingQueue<std::string> &received_queue, BlockingQueue<std::string> &to_send_queue);

    void run();

};


#endif //ROCKET_LEAGUE_GAME_H
