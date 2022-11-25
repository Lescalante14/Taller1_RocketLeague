//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H


#include <istream>

#include "client/helpers/MockProvider.h"
#include "client/presentation/ClientMatch.h"
#include "common/non_blocking_queue.h"
#include "common/blocking_queue.h"

class Game {

private:
    NonBlockingQueue<std::string> &input_queue;
    BlockingQueue<std::string> &exit_queue;

    std::string popGameState(const std::string &actualState, bool *running);
public:
    Game(NonBlockingQueue<std::string> &input_queue, BlockingQueue<std::string> &exit_queue);

    void start(std::istream &input);

};


#endif //ROCKET_LEAGUE_GAME_H
