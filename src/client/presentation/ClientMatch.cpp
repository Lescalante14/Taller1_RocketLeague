//
// Created by lescalante on 12/11/22.
//

#include "ClientMatch.h"

ClientMatch::ClientMatch(ClientMatchState state, SDL2pp::Renderer &renderer, MatchSetup setup)
: state(state), field(renderer), matchSetup(std::move(setup)), positionConverter(matchSetup),
ball(ClientBallState(state.get_ball_position_x(renderer),state.get_ball_position_y(renderer),0), renderer)
{
    for (auto &car : state.get_cars()) {
        cars.emplace_back(ClientCar(car, renderer));
    }
}

void ClientMatch::update(ClientMatchState s, SDL2pp::Renderer &renderer) {
	this->field.~Field();
	this->ball.~ClientBall();
	this->state.~ClientMatchState();
	
	this->field = Field(renderer);
	this->ball = ClientBall(ClientBallState(s.get_ball_position_x(renderer),
											s.get_ball_position_y(renderer),
											0), 
							renderer);
	this->state = s;
	cars.clear();

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
