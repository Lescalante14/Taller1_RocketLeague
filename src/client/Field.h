//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_FIELD_H
#define ROCKET_LEAGUE_FIELD_H


#include <string>
#include <SDL2pp/SDL2pp.hh>

class Field {
    SDL2pp::Texture texture;
public:
    explicit Field(SDL2pp::Renderer &renderer);
    Field(const std::string& imgPath, SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_FIELD_H
