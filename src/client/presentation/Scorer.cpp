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
, textureTime(renderer, font.RenderText_Blended(GetFormattedTime(time), SDL_Color{255, 255, 255, 255}))
, textureTeam1Name(renderer, font.RenderText_Blended("Team 1", SDL_Color{0, 0, 255, 255}))
, textureTeam2Name(renderer, font.RenderText_Blended("Team 2", SDL_Color{255, 0, 0, 255}))
, textureTeam1Scorer(renderer, font.RenderText_Blended("0", SDL_Color{255, 255, 255, 255}))
, textureTeam2Scorer(renderer, font.RenderText_Blended("0", SDL_Color{255, 255, 255, 255}))
, time(time), team1(0), team2(0)
{}

void Scorer::render(SDL2pp::Renderer &renderer, ClientScorerState state, MixerManager &mixerManager) {
    updateState(state, mixerManager);
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

void Scorer::updateState(ClientScorerState state, MixerManager &mixerManager) {
    // Update Time
    if (state.getTime() != time) {
        time = state.getTime();
        textureTime.Update(SDL2pp::NullOpt,font.RenderText_Blended(GetFormattedTime(time), SDL_Color{255, 255, 255, 255}));
    }

    // Update scorer team 1
    if (state.getTeam1() != team1) {
        mixerManager.playGoalSound();
        team1 = state.getTeam1();
        textureTeam1Scorer.Update(SDL2pp::NullOpt, font.RenderText_Blended(std::to_string(team1), SDL_Color{255, 255, 255, 255}));
    }

    // Update scorer team 2
    if (state.getTeam2() != team2) {
        mixerManager.playGoalSound();
        team2 = state.getTeam2();
        textureTeam2Scorer.Update(SDL2pp::NullOpt, font.RenderText_Blended(std::to_string(team2), SDL_Color{255, 255, 255, 255}));
    }
}

std::string Scorer::GetFormattedTime(int _time) {
    int minutes = _time/60;
    int seconds = _time%60;
    std::string separator = seconds < 10 ? ":0" : ":";
    return std::to_string(minutes) + separator + std::to_string(seconds);
}
