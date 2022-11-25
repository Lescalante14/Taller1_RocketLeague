//
// Created by lescalante on 17/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTBALLSTATE_H
#define ROCKET_LEAGUE_CLIENTBALLSTATE_H


#include <SDL2pp/Renderer.hh>
#include "common/ball_state.h"

class ClientBallState {
    //BallState wrappeeState; cuando habilite esto quitar los 3 attr

    // Positions in Cm
    int position_x;
    int position_y;
    int angle;
public:

    ClientBallState(int position_x, int position_y, int angle);
    // in Cm
    int get_position_x();
    // in Cm
    int get_position_y();
    int get_angle();
};


#endif //ROCKET_LEAGUE_CLIENTBALLSTATE_H
