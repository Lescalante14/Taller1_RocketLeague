//
// Created by lescalante on 21/11/22.
//

#include "Scorer.h"

#define SCORER_IMG_WIDTH 625
#define SCORER_IMG_HEIGHT 120

Scorer::Scorer(SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/scorer.png").SetColorKey(true, 0))
{}

void Scorer::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)-SCORER_IMG_WIDTH/2, 0, SCORER_IMG_WIDTH, SCORER_IMG_HEIGHT));
}
