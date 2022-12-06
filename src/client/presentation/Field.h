//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_FIELD_H
#define ROCKET_LEAGUE_FIELD_H


#include <string>
#include <SDL2pp/SDL2pp.hh>

#include "client/helpers/PositionConverter.h"
#include "Scorer.h"
#include "client/model/ClientScorerState.h"
#include "client/MixerManager.h"

class Field {
    SDL2pp::Texture fieldTexture;
    SDL2pp::Texture goalTexture1;
    SDL2pp::Texture goalTexture2;
    Scorer scorer;
public:
    explicit Field(SDL2pp::Renderer &renderer, int time);

    void render(SDL2pp::Renderer &renderer, PositionConverter &converter, ClientScorerState scorerState, MixerManager &mixerManager);
};


#endif //ROCKET_LEAGUE_FIELD_H
