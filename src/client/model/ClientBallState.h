//
// Created by lescalante on 17/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTBALLSTATE_H
#define ROCKET_LEAGUE_CLIENTBALLSTATE_H


#include "../../common/ball_state.h"
#include "SDL2pp/Renderer.hh"

class ClientBallState {
    //BallState wrappeeState; cuando habilite esto quitar los 3 attr
    int position_x;
    int position_y;
    int angle;
public:

    ClientBallState(int position_x, int position_y, int angle);
    int get_position_x(SDL2pp::Renderer &renderer);
    int get_position_y(SDL2pp::Renderer &renderer);
    int get_angle();
};


#endif //ROCKET_LEAGUE_CLIENTBALLSTATE_H
