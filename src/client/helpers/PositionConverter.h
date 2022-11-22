//
// Created by lescalante on 19/11/22.
//

#ifndef ROCKET_LEAGUE_POSITIONCONVERTER_H
#define ROCKET_LEAGUE_POSITIONCONVERTER_H


#include "SDL2pp/Renderer.hh"
#include "../../common/match_setup.h"

class PositionConverter {
    MatchSetup matchSetup;

public: // TODO: make &renderer attr

    explicit PositionConverter(MatchSetup &setup);

    int convert_CM_to_PX_In_X_axis(int pos, SDL2pp::Renderer &renderer);
    int convert_CM_to_PX_In_Y_axis(int pos, SDL2pp::Renderer &renderer);

    int get_car_width_in_PX(SDL2pp::Renderer &renderer);

    int get_car_height_in_PX(SDL2pp::Renderer &renderer);

    int get_radius_ball_in_PX(SDL2pp::Renderer &renderer);

    int get_goal_height_in_PX(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_POSITIONCONVERTER_H
