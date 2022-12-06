//
// Created by lescalante on 11/11/22.
//

#include "Field.h"


Field::Field(SDL2pp::Renderer &renderer, int time)
: fieldTexture(renderer, SDL2pp::Surface("./assets/field.jpg").SetColorKey(true, 0))
, goalTexture1(renderer, SDL2pp::Surface("./assets/goal1.png").SetColorKey(true, 0))
, goalTexture2(renderer, SDL2pp::Surface("./assets/goal2.png").SetColorKey(true, 0))
, scorer(renderer, time){}

void Field::render(SDL2pp::Renderer &renderer, PositionConverter &converter, ClientScorerState scorerState, MixerManager &mixerManager) {
    renderer.Copy(fieldTexture);
    int goalHeight = converter.get_goal_height_in_PX(renderer);
    renderer.Copy(goalTexture1,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(0, renderer.GetOutputHeight()-goalHeight, goalHeight/4, goalHeight));
    renderer.Copy(goalTexture2,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(renderer.GetOutputWidth()-goalHeight/4, renderer.GetOutputHeight()-goalHeight, goalHeight/4, goalHeight),
                  0,
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_HORIZONTAL);
    scorer.render(renderer, scorerState, mixerManager);
}
