//
// Created by lescalante on 17/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTBALLSTATE_H
#define ROCKET_LEAGUE_CLIENTBALLSTATE_H


#include <SDL2pp/Renderer.hh>
#include "common/ball_state.h"

class ClientBallState {

    BallState wrappeeState;
public:

    explicit ClientBallState(BallState state);

    // in Cm
    int get_position_x();
    // in Cm
    int get_position_y();
    int get_angle();

    shot_type get_shot_type();
};


#endif //ROCKET_LEAGUE_CLIENTBALLSTATE_H
