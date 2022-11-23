#ifndef B2_BALL_H
#define B2_BALL_H

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

#include "car.h"

enum shot_type {NONE, FLIP_SHOT, PURPLE_SHOT, RED_SHOT, GOLD_SHOT};
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
	void applyShotEffect(shot_type type);
	shot_type applyShotEffect(Car &car);

	/*  Stats  */
	b2Vec2 getPosition();
	b2Vec2 getVelocity();
	float getRadius();
	float getAngle();

	~Ball();
};

#endif
