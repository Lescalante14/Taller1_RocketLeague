//
// Created by lescalante on 06/12/22.
//

#ifndef ROCKET_LEAGUE_GOALANIMATION_H
#define ROCKET_LEAGUE_GOALANIMATION_H

#include "SDL2pp/SDL2pp.hh"

class GoalAnimation {
    SDL2pp::Texture texture;
    int currentFrame = 1;

public:
    explicit GoalAnimation(SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect rect);
};


#endif //ROCKET_LEAGUE_GOALANIMATION_H
