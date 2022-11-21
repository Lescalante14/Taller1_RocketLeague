#include <inc/box2d/box2d.h>
#include <stdint.h>

#include <vector>
#include <map>

#include "common/match_state.h"
#include "car.h"
#include "ball.h"


class GameModel { 
	private:
	b2World world;

	std::map<int, Car> cars;
	Ball ball;

	void setLimits(int height, int length);

	public:
	GameModel(uint8_t cars_amount);
	void step();
	void updateGame(UserAction a);
	MatchState getState();
	~GameModel();
};