//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTCARSTATE_H
#define ROCKET_LEAGUE_CLIENTCARSTATE_H


#include <cstdint>
#include <string>
#include "../../common/car_state.h"
#include "SDL2pp/Renderer.hh"

class ClientCarState {
private:
    CarState wrappeeState;
    bool _isRightPush;
    bool _isLeftPush;
    bool _isUpPush;
    bool _isDownPush;
public:
    explicit ClientCarState(CarState state);

    uint8_t get_id();
    uint8_t get_nitro_percentage();
    bool get_nitro_activated();
    int get_position_x();
    int get_position_y();
    int get_angle();

    bool is_oriented_right();

    [[nodiscard]] bool isRightPush() const;

    void setRightIsPushed(bool isPushed);
};


#endif //ROCKET_LEAGUE_CLIENTCARSTATE_H
