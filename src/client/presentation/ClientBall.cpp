//
// Created by lescalante on 17/11/22.
//

#include "ClientBall.h"

#include <utility>
#include "client/helpers/PositionConverter.h"

#define MAX_SHOT_STEPS 200


ClientBall::ClientBall(ClientBallState state, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("/var/rocket_league/ball.png").SetColorKey(true, 0))
, superShotTexture(renderer, SDL2pp::Surface("/var/rocket_league/shotBall.png").SetColorKey(true, 255))
, simpleShotTexture(renderer, SDL2pp::Surface("/var/rocket_league/shotBallAir.png").SetColorKey(true, 0))
, state(std::move(state)){}

void ClientBall::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter, MixerManager &mixerManager) {
    int posX = positionConverter.get_X_position_ball_in_PX(state.get_position_x(),renderer);
    int posY = positionConverter.get_Y_position_ball_in_PX(state.get_position_y(), renderer);
    int radiusBall = positionConverter.get_radius_ball_in_PX(renderer);

    renderShot(renderer, posX, posY, radiusBall, state.get_angle(), mixerManager);

    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, radiusBall*2, radiusBall*2),
                  -state.get_angle(),
                  SDL2pp::NullOpt,
                  SDL_FLIP_NONE
    );
}

void ClientBall::update(ClientBallState _state) {
    state = std::move(_state);
}

void ClientBall::renderShot(SDL2pp::Renderer &renderer, int posX, int posY, int radius, int angle, MixerManager &mixerManager) {
	if (last_shot == shot_type::NONE ||
		shot_steps > MAX_SHOT_STEPS) {
		
		last_shot = state.get_shot_type();
		shot_steps = 0;
	}

	switch (last_shot) {
        case NONE:
            return;

		case FLIP_SHOT:
            // Logic rendering in copy because its other texture
            if(shot_steps == 0) {
                mixerManager.playSimpleShotSound();
            }
			break;

		case PURPLE_SHOT:
            superShotTexture.SetColorMod(127, 0, 255);
            if(shot_steps == 0) {
                mixerManager.playSuperShotSound();
            }
			break;

		case RED_SHOT:
            superShotTexture.SetColorMod(255, 0, 127);
            if(shot_steps == 0) {
                mixerManager.playSuperShotSound();
            }
			break;

		case GOLD_SHOT:
            superShotTexture.SetColorMod(255, 255, 0);
            if(shot_steps == 0) {
                mixerManager.playSuperShotSound();
            }
			break;
	}

    int diameter = int(((float)radius*2)*1.5); // 50% bigger than ball
    renderer.Copy(last_shot == shot_type::FLIP_SHOT ? simpleShotTexture : superShotTexture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect((int)((float)posX-(float)radius/2), (int)((float)posY-(float)radius/2), diameter, diameter),
                  -angle,
                  SDL2pp::NullOpt,
                  SDL_FLIP_NONE
    );
	this->shot_steps++;
}
