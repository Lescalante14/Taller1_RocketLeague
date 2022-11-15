#include <inc/box2d/box2d.h>
#include <list>

#include "car.h"
#include "car.h"
#include "ball.h"

class GameModel { 
	private:
	b2World world;

	std::list<Car> cars;
	Ball ball;

	public:
	GameModel();
	void step();
	void update_game(MatchState &s);
	~GameModel();
};