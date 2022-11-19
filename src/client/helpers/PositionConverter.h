//
// Created by lescalante on 19/11/22.
//

#ifndef ROCKET_LEAGUE_POSITIONCONVERTER_H
#define ROCKET_LEAGUE_POSITIONCONVERTER_H


#include "SDL2pp/Renderer.hh"

class PositionConverter {

public:

    int convert_CM_to_PX_In_X_axis(int pos, SDL2pp::Renderer &renderer);
    int convert_CM_to_PX_In_Y_axis(int pos, SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_POSITIONCONVERTER_H
