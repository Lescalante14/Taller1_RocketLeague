//
// Created by lescalante on 17/11/22.
//

#include "ClientBall.h"

#include <utility>
#include "client/helpers/PositionConverter.h"

#define MAX_SHOT_STEPS 200


ClientBall::ClientBall(ClientBallState state, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/ball.png").SetColorKey(true, 0))
, shotTexture(renderer, SDL2pp::Surface("./assets/shotBall.png").SetColorKey(true, 255))
, state(std::move(state)){}

void ClientBall::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posX = positionConverter.get_X_position_ball_in_PX(state.get_position_x(),renderer);
    int posY = positionConverter.get_Y_position_ball_in_PX(state.get_position_y(), renderer);
    int radiusBall = positionConverter.get_radius_ball_in_PX(renderer);

    renderShot(renderer, posX, posY, radiusBall);

    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, radiusBall*2, radiusBall*2),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_NONE
    );
}

void ClientBall::update(ClientBallState _state) {
    state = std::move(_state);
}

// TODO: get color from a map depending the shotType and update texture
void ClientBall::renderShot(SDL2pp::Renderer &renderer, int posX, int posY, int radius) {
	if (this->last_shot == shot_type::NONE ||
		this->shot_steps > MAX_SHOT_STEPS) {
		
		this->last_shot = state.get_shot_type();
		this->shot_steps = 0;
	}

	switch (this->last_shot) {
		case FLIP_SHOT:
			break;
		
		case PURPLE_SHOT:
			break;
		
		case RED_SHOT:
			break;
		
		case GOLD_SHOT:
			break;

		case NONE:
			return;
	}

    int diameter = int(((float)radius*2)*1.5); // 50% bigger than ball
    renderer.Copy(shotTexture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((int)((float)posX-(float)radius/2), (int)((float)posY-(float)radius/2), diameter, diameter),
                  0.0,
                  SDL2pp::NullOpt,
                  SDL_FLIP_NONE
    );
	this->shot_steps++;
}
