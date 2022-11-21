#include <inc/box2d/box2d.h>

#include "car.h"
#include "ball.h"

class GameModel { 
	private:
	b2World world;

	Car car_1;
	Car car_2;
	Ball ball;

	public:
	GameModel();
	void step();
	~GameModel();
};