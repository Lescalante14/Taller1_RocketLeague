#include <box2d/b2_circle_shape.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>

#include "ball.h"

#define SMALL_RADIUS 0.75f
#define MED_RADIUS   1.5f
#define BIG_RADIUS   2.0f

#define FLIP_SHOT_IMPULSE   30.0f
#define PURPLE_SHOT_IMPULSE 40.0f
#define RED_SHOT_IMPULSE    60.0f
#define GOLD_SHOT_IMPULSE   70.0f

#define BALL_DENSITY 0.5f

#define BASE_DISTANCE 0.40f
#define CLOSE_DISTANCE  0.15f


Ball::Ball(b2World &world, float x, float y, ball_size size) {
	float radius = 0;
	
	switch (size) {
	case SMALL_BALL:
		radius = SMALL_RADIUS;
	break;
	
	case BIG_BALL:
		radius = BIG_RADIUS;
	break;

	// default size is MED_BALL
	default:
		radius = MED_RADIUS;
	}

	b2BodyDef ballDef;
	ballDef.type = b2_dynamicBody;
	ballDef.position.Set(x, y);
	this->ball = world.CreateBody(&ballDef);
	
	b2CircleShape ballShape;
	ballShape.m_radius = radius;
	this->_radius = radius;
	this->ball->CreateFixture(&ballShape, BALL_DENSITY);
}

/*  Actions  */

void Ball::move(float x, float y) {
	this->ball->SetTransform(b2Vec2(x, y), this->ball->GetAngle());
}


void Ball::resize(ball_size newsz) {
	float radius = 0;

	switch (newsz) {
	case SMALL_BALL:
		radius = SMALL_RADIUS;
	break;
	case BIG_BALL:
		radius = BIG_RADIUS;
	break;
	// default size is MED_BALL
	default:
		radius = MED_RADIUS;
	}
	this->ball->GetFixtureList()->GetShape()->m_radius = radius;
	this->_radius = radius;
	// b2CircleShape ballShape;
	// ballShape.m_radius = radius;
	// this->ball->DestroyFixture(this->ball->GetFixtureList());
	// this->ball->CreateFixture(&ballShape, BALL_DENSITY);
}


void Ball::applyShotEffect(shot_type type) {
	b2Vec2 i(0, 0);
	
	for (b2ContactEdge* c = this->ball->GetContactList(); c; c = c->next) {
		b2Vec2 dir = c->other->GetLinearVelocity();
		dir.Normalize();
		i += dir;
		i.Normalize();
	}
	this->ball->GetContactList();

	switch (type) {
	case FLIP_SHOT:
		i *= FLIP_SHOT_IMPULSE;
		break;

	case RED_SHOT:
		i *= RED_SHOT_IMPULSE;
		break;
	
	case PURPLE_SHOT:
		i *= PURPLE_SHOT_IMPULSE;
		break;
	
	case GOLD_SHOT:
		i *= GOLD_SHOT_IMPULSE;
		break;
	
	default:
		return;
	}
	this->ball->ApplyLinearImpulseToCenter(i, true);
}


shot_type Ball::applyShotEffect(Car &car) {
	float d = (car.getPosition() - this->ball->GetPosition()).Length();
	
	if (d > BASE_DISTANCE) {
		return shot_type::NONE;
	}

	if (car.hasFlipped()) {
		if (d <= CLOSE_DISTANCE) {
			/* Flip Shot */
			if (car.isPointingTo(this->ball->GetPosition())) {
				this->applyShotEffect(shot_type::FLIP_SHOT);
				return shot_type::FLIP_SHOT;
			}
			
			/* Gold Shot */
			/* the car is in oposite direction to the ball */
			this->applyShotEffect(shot_type::GOLD_SHOT);
			return shot_type::GOLD_SHOT;

		}		
		/* Red Shot */
		this->applyShotEffect(shot_type::RED_SHOT);
		return shot_type::RED_SHOT;

	/* Purple Shot */
	/* if angle is between 80 and 100 degrees (car is standing up) */
	} else if (sin(car.getAngle()) > 0.9848f) {
		this->applyShotEffect(shot_type::PURPLE_SHOT);
		return shot_type::PURPLE_SHOT;
	}

	return shot_type::NONE;
}

void Ball::reset(float x, float y) {
	this->move(x, y);
	this->ball->SetAngularVelocity(0);
	this->ball->SetLinearVelocity(b2Vec2(0, 0));
}



/*  Stats  */

b2Vec2 Ball::getPosition() {
	return this->ball->GetPosition();
}

b2Vec2 Ball::getVelocity() {
	return this->ball->GetLinearVelocity();
}

uint16_t Ball::getAngle() {
	uint16_t deg_angle = (uint16_t) abs(this->ball->GetAngle() * 180.0f / b2_pi + 360.0f);
	return deg_angle % 360;
}

shot_type Ball::getShot() {
	return this->last_shot;
}

float Ball::getRadius() {
	return this->_radius;
}

Ball::~Ball() {}


