//
// Created by lescalante on 17/11/22.
//

#include "ClientBallState.h"
#include "../helpers/PositionConverter.h"

ClientBallState::ClientBallState(int position_x, int position_y, int angle)
: position_x(position_x), position_y(position_y), angle(angle){}

int ClientBallState::get_position_x(SDL2pp::Renderer &renderer) {
    PositionConverter converter;
    return converter.convert_CM_to_PX_In_X_axis(position_x, renderer);//wrappeeState.getPositionX();
}

int ClientBallState::get_position_y(SDL2pp::Renderer &renderer) {
    PositionConverter converter;
    return converter.convert_CM_to_PX_In_Y_axis(position_y, renderer);//wrappeeState.getPositionY();
}

int ClientBallState::get_angle() {
    return angle;//wrappeeState.getAngle();
}
