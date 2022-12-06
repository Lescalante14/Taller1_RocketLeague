//
// Created by lescalante on 04/12/22.
//

#include <SDL_render.h>
#include "ClientNitroBar.h"
#include "SDL2pp/Surface.hh"

#define MAX_HEIGHT 25

ClientNitroBar::ClientNitroBar(SDL2pp::Renderer &renderer)
: emptyNitroBar(renderer, SDL2pp::Surface("/var/rocket_league/nitroEmpty.png").SetColorKey(true, 0))
, fullNitroBar(renderer, SDL2pp::Surface("/var/rocket_league/nitroFull.png").SetColorKey(true, 0)){}

void ClientNitroBar::render(SDL2pp::Renderer &renderer, uint8_t nitroPercentage, int posX, int posY, int carWidth,
                            int carHeight, bool isOrientedRight) {

    int barWidth = carWidth*3/4;
    int barHeight = carHeight/2 < MAX_HEIGHT ? carHeight/2 : MAX_HEIGHT;
    renderer.Copy(emptyNitroBar,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX+carWidth/8, posY-30, barWidth, barHeight),
                  0.0,
                  SDL2pp::NullOpt,
                  isOrientedRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
    );

    float fillWidth = (float)(barWidth-2)*((float)nitroPercentage/(float)100);
    renderer.Copy(fullNitroBar,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX+carWidth/8, posY-30, (int)fillWidth, barHeight),
                  0.0,
                  SDL2pp::NullOpt,
                  isOrientedRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
    );
}
