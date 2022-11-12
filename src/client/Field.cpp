//
// Created by lescalante on 11/11/22.
//

#include "Field.h"

Field::Field(SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/field.jpg").SetColorKey(true, 0)) {}

Field::Field(const std::string& imgPath, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface(imgPath).SetColorKey(true, 0)) {}

void Field::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture);
}
