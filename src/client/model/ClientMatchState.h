//
// Created by lescalante on 12/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTMATCHSTATE_H
#define ROCKET_LEAGUE_CLIENTMATCHSTATE_H


#include <cstdint>
#include <vector>
#include "ClientCarState.h"
#include "../../common/match_state.h"
#include "ClientBallState.h"

class ClientMatchState {
private:
    ClientBallState ballState;
    MatchState wrappeeState;
    std::vector<ClientCarState> cars;
public:
    explicit ClientMatchState(MatchState state);

    uint8_t get_playing();
    uint16_t get_time();
    uint8_t get_scorer_1();
    uint8_t get_scorer_2();
    uint8_t get_cars_quantity();
    int get_ball_position_x(SDL2pp::Renderer &renderer);
    int get_ball_position_y(SDL2pp::Renderer &renderer);
    int get_ball_angle();
    std::vector<ClientCarState> get_cars();
};


#endif //ROCKET_LEAGUE_CLIENTMATCHSTATE_H
