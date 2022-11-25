//
// Created by lescalante on 12/11/22.
//

#include "ClientMatch.h"

ClientMatch::ClientMatch(ClientMatchState state, SDL2pp::Renderer &renderer, MatchSetup &setup)
: state(std::move(state)), field(renderer), matchSetup(setup), positionConverter(matchSetup),
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


void ClientMatch::updateState(ClientMatchState newMatchState, SDL2pp::Renderer &renderer) {

    state = std::move(newMatchState);
    ball.update(ClientBallState(state.get_ball_position_x(), state.get_ball_position_y(), state.get_ball_angle()));
    /*for (size_t i = 0; i < cars.size(); ++i) {
        cars.at(i).updateState(state.get_cars().at(i));
    }*/
    // TODO: updatear autos en vez de crear nuevos
    cars.clear();
    for (auto &car : state.get_cars()) {
        cars.emplace_back(ClientCar(car, renderer));
    }

}
