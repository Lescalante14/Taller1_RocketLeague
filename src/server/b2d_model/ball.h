#ifndef B2_BALL_H
#define B2_BALL_H

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

#include "car.h"
#include "common/ball_state.h"

enum ball_size {SMALL_BALL, MED_BALL, BIG_BALL};


class Ball {
	private:
	float x, y;
	float _radius = 0;
	b2Body *ball = nullptr;
	
	public:
	Ball(b2World &world, float x, float y, ball_size size);
	
	/*  Actions  */
	void move(float x, float y);
	void resize(ball_size newsz);
	void applyShotEffect(shot_type type, b2Vec2 &dir);
	shot_type applyShotEffect(Car &car);
	void reset(float x, float y);

	/*  Stats  */
	b2Vec2 getPosition();
	b2Vec2 getVelocity();
	uint16_t getAngle();
	float getRadius();

	~Ball();
};

#endif
