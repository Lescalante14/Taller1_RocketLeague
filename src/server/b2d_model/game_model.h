#include <inc/box2d/box2d.h>
#include <map>

#include "common/match_state.h"
#include "car.h"
#include "ball.h"

class GameModel { 
	private:
	b2World world;

	std::map<int, Car> cars;
	Ball ball;

	public:
	GameModel();
	void step();
	void updateGame(MatchState &s);
	MatchState getState();
	~GameModel();
};