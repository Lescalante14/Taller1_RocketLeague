#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

enum shot_types {NONE, FLIP_SHOT, RED_SHOT, PURPLE_SHOT, GOLD_SHOT};
enum ball_sizes {SMALL_BALL, MED_BALL, BIG_BALL};

class Ball {
	private:
	float x, y;
	b2Body *ball = nullptr;
	int hit_type;

	public:
	Ball(b2World &world, float x, float y , uint8_t size);
	void move(float x, float y);
	void resize(uint8_t newsz);
};