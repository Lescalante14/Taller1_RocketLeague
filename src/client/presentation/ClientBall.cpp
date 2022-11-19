//
// Created by lescalante on 17/11/22.
//

#include "ClientBall.h"
#define BALL_PIC_WIDTH 840
#define BALL_PIC_HEIGHT 859
#define BALL_WIDTH (BALL_PIC_WIDTH/6)
#define BALL_HEIGHT (BALL_PIC_HEIGHT/6)

ClientBall::ClientBall(ClientBallState state, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/ball.png").SetColorKey(true, 0))
        , state(state){}

void ClientBall::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture,
                  SDL2pp::Rect(0, 0, BALL_PIC_WIDTH, BALL_PIC_HEIGHT),
            //SDL2pp::Rect(50, renderer.GetOutputHeight()-100, BALL_WIDTH, BALL_HEIGHT),
                  SDL2pp::Rect(state.get_position_x(renderer), state.get_position_y(renderer), BALL_WIDTH, BALL_HEIGHT),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_NONE
    );
}
