//
// Created by lescalante on 04/12/22.
//

#ifndef ROCKET_LEAGUE_CLIENTNITROBAR_H
#define ROCKET_LEAGUE_CLIENTNITROBAR_H


#include "SDL2pp/Texture.hh"
#include "SDL2pp/Renderer.hh"

class ClientNitroBar {

    SDL2pp::Texture emptyNitroBar;
    SDL2pp::Texture fullNitroBar;

public:
    explicit ClientNitroBar(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, uint8_t nitroPercentage, int posX, int posY, int carWidth, int carHeight,
                bool isOrientedRight);
};


#endif //ROCKET_LEAGUE_CLIENTNITROBAR_H
