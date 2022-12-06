//
// Created by lescalante on 11/11/22.
//

#include "Field.h"

#define MAX_STEPS_ANIMATION 1000

Field::Field(SDL2pp::Renderer &renderer, int time)
: fieldTexture(renderer, SDL2pp::Surface("./assets/field.jpg").SetColorKey(true, 0))
, goalTexture1(renderer, SDL2pp::Surface("./assets/goal1.png").SetColorKey(true, 0))
, goalTexture2(renderer, SDL2pp::Surface("./assets/goal2.png").SetColorKey(true, 0))
, scorer(renderer, time)
, goalAnimation(renderer){}

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
                  SDL2pp::NullOpt,
                  SDL_FLIP_HORIZONTAL);

    renderGoalAnimation(renderer, scorerState, goalHeight);

    scorer.render(renderer, scorerState, mixerManager);
}

// TODO: refactorizar esto para mostrar la animación hasta que empiece la repetición
void Field::renderGoalAnimation(SDL2pp::Renderer &renderer, ClientScorerState scorerState, int goalHeight) {
    if (shotStepsAnimation > MAX_STEPS_ANIMATION) {
        shotStepsAnimation = 0;
        team1Goal = false;
        team2Goal = false;
    }
    if (scorerState.getTeam1() > scorerTeam1 || team1Goal) {
        team1Goal = true;
        scorerTeam1 = scorerState.getTeam1() > scorerTeam1 ? scorerState.getTeam1() : scorerTeam1;
        goalAnimation.render(renderer,
                             SDL2pp::Rect(renderer.GetOutputWidth()-goalHeight/4, renderer.GetOutputHeight()-goalHeight, goalHeight/4, goalHeight));
        shotStepsAnimation++;
    } else if (scorerState.getTeam2() > scorerTeam2 || team2Goal) {
        team2Goal = true;
        scorerTeam2 = scorerState.getTeam2() > scorerTeam2 ? scorerState.getTeam2() : scorerTeam2;
        goalAnimation.render(renderer,
                             SDL2pp::Rect(0, renderer.GetOutputHeight()-goalHeight, goalHeight/4, goalHeight));
        shotStepsAnimation++;
    }
}
