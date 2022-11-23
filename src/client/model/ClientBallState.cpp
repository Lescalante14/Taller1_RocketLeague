//
// Created by lescalante on 17/11/22.
//

#include "ClientBallState.h"

ClientBallState::ClientBallState(int position_x, int position_y, int angle)
: position_x(position_x), position_y(position_y), angle(angle){}

int ClientBallState::get_position_x() {
    return position_x;//wrappeeState.getPositionX();
}

int ClientBallState::get_position_y() {
    return position_y;//wrappeeState.getPositionY();
}

int ClientBallState::get_angle() {
    return angle;//wrappeeState.getAngle();
}
