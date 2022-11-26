//
// Created by lescalante on 12/11/22.
//

#include "ClientMatch.h"

ClientMatch::ClientMatch(ClientMatchState _state, SDL2pp::Renderer &renderer, MatchSetup &setup)
: state(std::move(_state)), field(renderer), matchSetup(setup), positionConverter(matchSetup),
ball(ClientBallState(state.get_ball_position_x(),state.get_ball_position_y(),0), renderer)
{
    for (auto &car : state.get_cars()) {
        cars.emplace_back(ClientCar(car, renderer));
    }
}

void ClientMatch::render(SDL2pp::Renderer &renderer) {
    renderer.Clear();
    field.render(renderer, positionConverter);
    ball.render(renderer, positionConverter);

    for (auto &car : cars) {
        car.render(renderer, positionConverter);
    }
    renderer.Present();
}

uint8_t ClientMatch::getCarIdAssigned() {
    return matchSetup.get_car_id_assigned();
}


void ClientMatch::updateState(ClientMatchState newMatchState) {

    ball.update(ClientBallState(newMatchState.get_ball_position_x(), newMatchState.get_ball_position_y(), newMatchState.get_ball_angle()));
    for (size_t i = 0; i < newMatchState.get_cars().size(); ++i) {
        cars.at(i).updateState(newMatchState.get_cars().at(i));
    }
    state = std::move(newMatchState);
}
