#ifndef B2D_GAME_MODEL_H
#define B2D_GAME_MODEL_H

#include <box2d/box2d.h>
#include <stdint.h>

#include <vector>
#include <map>

#include "common/match_state.h"
#include "common/user_action.h"
#include "car.h"
#include "ball.h"


class GameModel { 
	private:
	b2World world;
	int step_count = 0;
	
	std::map<uint8_t, Car> cars;
	Ball ball;

	void setLimits(int height, int length);

	public:
	GameModel(size_t cars_amount);
	void step();
	void updateGame(UserAction &a);
	MatchState getState();
	~GameModel();
};

#endif
