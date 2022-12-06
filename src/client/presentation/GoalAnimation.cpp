//
// Created by lescalante on 06/12/22.
//

#include "GoalAnimation.h"

#define NUM_FRAMES 5
#define SIZE_FRAME 181

GoalAnimation::GoalAnimation(SDL2pp::Renderer &renderer)
        : texture(renderer, SDL2pp::Surface("/var/rocket_league/explosionGoalAnimation.png").SetColorKey(true, 255)){}

void GoalAnimation::render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest) {
    renderer.Copy(
            texture,
            SDL2pp::Rect(1 + (1 + SIZE_FRAME) * currentFrame, 0, SIZE_FRAME, SIZE_FRAME),
            dest,
            0,
            SDL2pp::NullOpt,
            SDL_FLIP_NONE
    );

    if (currentFrame >= NUM_FRAMES) {
        currentFrame = 1;
    } else {
        currentFrame++;
    }
}
