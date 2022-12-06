//
// Created by lescalante on 17/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTBALL_H
#define ROCKET_LEAGUE_CLIENTBALL_H

#include <SDL2pp/SDL2pp.hh>
#include "client/model/ClientBallState.h"
#include "client/helpers/PositionConverter.h"
#include "client/MixerManager.h"

class ClientBall {
    SDL2pp::Texture texture;
    SDL2pp::Texture superShotTexture;
    SDL2pp::Texture simpleShotTexture;
    ClientBallState state;
	shot_type last_shot = shot_type::NONE;
	size_t shot_steps = 0;

    void renderShot(SDL2pp::Renderer &renderer, int posX, int posY, int radius, int angle,MixerManager &manager);

public:

    ClientBall(ClientBallState state, SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter, MixerManager &manager);

    void update(ClientBallState _state);
};


#endif //ROCKET_LEAGUE_CLIENTBALL_H
