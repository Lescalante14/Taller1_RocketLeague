//
// Created by lescalante on 11/11/22.
//

#include "Field.h"
#include "../helpers/PositionConverter.h"

#define SCORER_IMG_WIDTH 625
#define SCORER_IMG_HEIGHT 120

Field::Field(SDL2pp::Renderer &renderer)
: fieldTexture(renderer, SDL2pp::Surface("./assets/field.jpg").SetColorKey(true, 0))
, goalTexture1(renderer, SDL2pp::Surface("./assets/goal1.png").SetColorKey(true, 0))
, goalTexture2(renderer, SDL2pp::Surface("./assets/goal2.png").SetColorKey(true, 0))
, scorerTexture(renderer, SDL2pp::Surface("./assets/scorer.png").SetColorKey(true, 0)) {}

void Field::render(SDL2pp::Renderer &renderer, PositionConverter &converter) {
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
    renderer.Copy(scorerTexture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)-SCORER_IMG_WIDTH/2, 0, SCORER_IMG_WIDTH, SCORER_IMG_HEIGHT));
}
