//
// Created by lescalante on 12/11/22.
//

#include "ClientMatch.h"

ClientMatch::ClientMatch(ClientMatchState state, SDL2pp::Renderer &renderer)
: state(state), field(renderer),
ball(ClientBallState(state.get_ball_position_x(renderer),state.get_ball_position_y(renderer),0), renderer)
{
    for (auto &car : state.get_cars()) {
        cars.emplace_back(ClientCar(car, renderer));
    }
}

void ClientMatch::render(SDL2pp::Renderer &renderer) {
    renderer.Clear();
    field.render(renderer);
    ball.render(renderer);
    for (auto &car : cars) {
        car.render(renderer);
    }
    renderer.Present();
}
