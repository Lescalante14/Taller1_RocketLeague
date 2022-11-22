//
// Created by lescalante on 21/11/22.
//

#ifndef ROCKET_LEAGUE_SCORER_H
#define ROCKET_LEAGUE_SCORER_H

#include "SDL2pp/SDL2pp.hh"

class Scorer {
    SDL2pp::Texture texture;
public:
    explicit Scorer(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_SCORER_H
