#include "box2d/b2_body.h"

enum shot_types {NONE, FLIP_SHOT, RED_SHOT, PURPLE_SHOT, GOLD_SHOT};

class Ball {
	private:
	float x, y;
	b2Body *ball = nullptr;
	int hit_type;

	public:
	Ball();
	Ball(b2World *world, float x, float y);
};