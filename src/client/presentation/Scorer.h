//
// Created by lescalante on 21/11/22.
//

#ifndef ROCKET_LEAGUE_SCORER_H
#define ROCKET_LEAGUE_SCORER_H

#include <SDL2pp/SDL2pp.hh>
#include "client/model/ClientScorerState.h"
#include "client/MixerManager.h"

class Scorer {
    SDL2pp::Font font;
    SDL2pp::Texture textureScorer;
    SDL2pp::Texture textureTime;
    SDL2pp::Texture textureTeam1Name;
    SDL2pp::Texture textureTeam2Name;
    SDL2pp::Texture textureTeam1Scorer;
    SDL2pp::Texture textureTeam2Scorer;
    int time;
    int team1;
    int team2;
public:
    explicit Scorer(SDL2pp::Renderer &renderer, int time);

    void render(SDL2pp::Renderer &renderer, ClientScorerState state, MixerManager &mixerManager);

    void updateState(ClientScorerState state, MixerManager &mixerManager);

    std::string GetFormattedTime(int _time);
};


#endif //ROCKET_LEAGUE_SCORER_H
