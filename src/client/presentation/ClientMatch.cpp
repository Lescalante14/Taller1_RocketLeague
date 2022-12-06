//
// Created by lescalante on 12/11/22.
//

#include "ClientMatch.h"
#include "client/model/ClientScorerState.h"

ClientMatch::ClientMatch(ClientMatchState _state, SDL2pp::Renderer &renderer, MixerManager &_mixerManager, MatchSetup &setup)
: state(std::move(_state)), mixerManager(_mixerManager), field(renderer, state.get_time()), matchSetup(setup), positionConverter(matchSetup),
ball(state.get_ball_state(), renderer)
{
    int numCarsTeam1 = std::ceil((float)setup.get_cars_quantity()/(float)2);
    for (auto &car : state.get_cars()) {
        cars.emplace_back(car, car.get_id()+1 <= numCarsTeam1, renderer);
    }
}

void ClientMatch::render(SDL2pp::Renderer &renderer) {
    renderer.Clear();
    ClientScorerState scorerState(state.get_time(), state.get_scorer_1(), state.get_scorer_2());
    field.render(renderer, positionConverter, scorerState, mixerManager, state.is_repetition());
    ball.render(renderer, positionConverter, mixerManager);

    int index = 0;
    for (auto &car : cars) {
        car.render(renderer, positionConverter, index == matchSetup.get_car_id_assigned(), mixerManager);
        index++;
    }
    renderer.Present();
}

uint8_t ClientMatch::getCarIdAssigned() {
    return matchSetup.get_car_id_assigned();
}


void ClientMatch::updateState(ClientMatchState newMatchState) {

    ball.update(newMatchState.get_ball_state());
    for (size_t i = 0; i < newMatchState.get_cars().size(); ++i) {
        cars.at(i).updateState(newMatchState.get_cars().at(i));
    }
    state = std::move(newMatchState);
}
