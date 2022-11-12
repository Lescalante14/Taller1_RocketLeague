//
// Created by lescalante on 12/11/22.
//

#include "ClientMatchState.h"

ClientMatchState::ClientMatchState(MatchState state)
: wrappeeState(state), cars()
{
    for (auto &car : wrappeeState.get_cars()) {
        cars.emplace_back(CarState(car));
    }
}

uint16_t ClientMatchState::get_time() {
    return wrappeeState.get_time();
}

uint8_t ClientMatchState::get_playing() {
    return wrappeeState.get_playing();
}

uint8_t ClientMatchState::get_scorer_1() {
    return wrappeeState.get_scorer_1();
}

uint8_t ClientMatchState::get_scorer_2() {
    return wrappeeState.get_scorer_2();
}

uint8_t ClientMatchState::get_cars_quantity() {
    return wrappeeState.get_cars_quantity();
}

int ClientMatchState::get_ball_position_x() {
    return wrappeeState.get_ball_position_x();
}

int ClientMatchState::get_ball_position_y() {
    return wrappeeState.get_ball_position_y();
}

int ClientMatchState::get_ball_angle() {
    return 0;//wrappeeState.get_ball_angle();
}

std::vector<ClientCarState> ClientMatchState::get_cars() {
    return cars;
}

