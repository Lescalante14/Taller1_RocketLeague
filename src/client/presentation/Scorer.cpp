//
// Created by lescalante on 21/11/22.
//

#include "Scorer.h"
#include "client/model/ClientScorerState.h"

#define SCORER_IMG_WIDTH 625
#define SCORER_IMG_HEIGHT 120

Scorer::Scorer(SDL2pp::Renderer &renderer, int time)
: font("./assets/Vera.ttf", 26)
, textureScorer(renderer, SDL2pp::Surface("./assets/scorer.png").SetColorKey(true, 0))
, textureTime(renderer, font.RenderText_Blended(std::to_string(time), SDL_Color{255, 255, 255, 255}))
, textureTeam1Name(renderer, font.RenderText_Blended("Team 1", SDL_Color{0, 0, 255, 255}))
, textureTeam2Name(renderer, font.RenderText_Blended("Team 2", SDL_Color{255, 0, 0, 255}))
, textureTeam1Scorer(renderer, font.RenderText_Blended("0", SDL_Color{255, 255, 255, 255}))
, textureTeam2Scorer(renderer, font.RenderText_Blended("0", SDL_Color{255, 255, 255, 255}))
, time(time), team1(0), team2(0)
{}

void Scorer::render(SDL2pp::Renderer &renderer, ClientScorerState state) {
    updateState(renderer, state);
    renderer.Copy(textureScorer,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)-SCORER_IMG_WIDTH/2, 0, SCORER_IMG_WIDTH, SCORER_IMG_HEIGHT));

    renderer.Copy(textureTeam1Name,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)-200, 30, textureTeam1Name.GetWidth(), textureTeam1Name.GetHeight()));

    renderer.Copy(textureTime,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)-(textureTime.GetWidth()/2), 30, textureTime.GetWidth(), textureTime.GetHeight()));

    renderer.Copy(textureTeam2Name,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)+100, 30, textureTeam2Name.GetWidth(), textureTeam2Name.GetHeight()));

    renderer.Copy(textureTeam1Scorer,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((renderer.GetOutputWidth()/2)-(SCORER_IMG_WIDTH/2)+25, 30, textureTeam1Scorer.GetWidth(), textureTeam1Scorer.GetHeight()));

    renderer.Copy(textureTeam2Scorer,
                      SDL2pp::NullOpt,
                      SDL2pp::Rect((renderer.GetOutputWidth()/2)+(SCORER_IMG_WIDTH/2)-40, 30, textureTeam2Scorer.GetWidth(), textureTeam2Scorer.GetHeight()));
}

void Scorer::updateState(SDL2pp::Renderer &renderer, ClientScorerState state) {
    /*if (state.getTime() != time) {
        textureTime = SDL2pp::Texture(renderer, font.RenderText_Blended(std::to_string(state.getTime()), SDL_Color{255, 255, 255, 255}));
        time = state.getTime();
    }*/
}
