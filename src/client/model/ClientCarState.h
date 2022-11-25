//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTCARSTATE_H
#define ROCKET_LEAGUE_CLIENTCARSTATE_H


#include <SDL2pp/Renderer.hh>
#include <cstdint>
#include <string>
#include "common/car_state.h"

class ClientCarState {
private:
    CarState wrappeeState;
public:
    explicit ClientCarState(CarState state);

    uint8_t get_id();
    uint8_t get_nitro_percentage();
    bool get_nitro_activated();
    // in Cm
    int get_position_x();
    // in Cm
    int get_position_y();
    int get_angle();

    bool is_oriented_right();
};


#endif //ROCKET_LEAGUE_CLIENTCARSTATE_H
