//
// Created by lescalante on 19/11/22.
//

#ifndef ROCKET_LEAGUE_POSITIONCONVERTER_H
#define ROCKET_LEAGUE_POSITIONCONVERTER_H


#include <SDL2pp/Renderer.hh>
#include "common/match_setup.h"

class PositionConverter {
    MatchSetup &matchSetup;

public: // TODO: make &renderer attr

    explicit PositionConverter(MatchSetup &setup);

    int get_X_position_car_in_PX(int pos, SDL2pp::Renderer &renderer);
    int get_Y_position_car_in_PX(int pos, SDL2pp::Renderer &renderer);

    int get_X_position_ball_in_PX(int cmPos, SDL2pp::Renderer &renderer);

    int get_Y_position_ball_in_PX(int cmPos, SDL2pp::Renderer &renderer);

    int get_car_width_in_PX(SDL2pp::Renderer &renderer);

    int get_car_height_in_PX(SDL2pp::Renderer &renderer);

    int get_radius_ball_in_PX(SDL2pp::Renderer &renderer);

    int get_goal_height_in_PX(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_POSITIONCONVERTER_H
