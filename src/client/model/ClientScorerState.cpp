//
// Created by lescalante on 01/12/22.
//

#include "ClientScorerState.h"

ClientScorerState::ClientScorerState(int time, int team1, int team2)
: time(time), team1(team1), team2(team2){}

int ClientScorerState::getTime() const {
    return time;
}

int ClientScorerState::getTeam1() const {
    return team1;
}

int ClientScorerState::getTeam2() const {
    return team2;
}
