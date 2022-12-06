#include <box2d/b2_circle_shape.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>

#include <iostream>

#include "ball.h"

#define SMALL_RADIUS 0.75f
#define MED_RADIUS   1.5f
#define BIG_RADIUS   2.0f

#define FLIP_SHOT_IMPULSE   30.0f
#define PURPLE_SHOT_IMPULSE 40.0f
#define RED_SHOT_IMPULSE    60.0f
#define GOLD_SHOT_IMPULSE   70.0f

#define BALL_DENSITY 0.3f

#define BASE_DISTANCE 5.0f
#define CLOSE_DISTANCE  3.0f


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
	ballDef.gravityScale = 0.5f;
	this->ball = world.CreateBody(&ballDef);
	
	b2CircleShape ballShape;
	ballShape.m_radius = radius;
	this->_radius = radius;

	b2FixtureDef fDef;
	fDef.shape = &ballShape;
	fDef.density = BALL_DENSITY;
	fDef.restitution = 0.5f;

	this->ball->CreateFixture(&fDef);
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


void Ball::applyShotEffect(shot_type type, b2Vec2 &dir) {
	b2Vec2 i = dir;
	i.Normalize();
	
	// for (b2ContactEdge* c = this->ball->GetContactList(); c; c = c->next) {
	// 	b2Vec2 dir = c->other->GetLinearVelocity();
	// 	dir.Normalize();
	// 	i += dir;
	// 	i.Normalize();
	// }
	// this->ball->GetContactList();

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
	b2Vec2 d = this->ball->GetPosition() - car.getPosition();
	std::cout << "FACING: " << car.getFacing() << ", ";
	std::cout << "DISTANCE: " << d.Length() << ", ";
	std::cout << "ANGLE: " << car.getRadAngle() << ", ";
	
	if (d.Length() > BASE_DISTANCE) {
		std::cout << "NONE SHOT 1\n";
		return shot_type::NONE;
	}

	if (car.hasFlipped()) {
		if (car.isPointingTo(this->ball->GetPosition())) {
			if (d.Length() > CLOSE_DISTANCE) {
				this->applyShotEffect(shot_type::FLIP_SHOT, d);
				std::cout << "FLIP SHOT\n";
				return shot_type::FLIP_SHOT;

			} else {
				/* Red Shot */
				this->applyShotEffect(shot_type::RED_SHOT, d);
				std::cout << "RED SHOT\n";
				return shot_type::RED_SHOT;

			}
		
		} else {
			/* Gold Shot */
			/* the car is in oposite direction to the ball */
			this->applyShotEffect(shot_type::GOLD_SHOT, d);
			std::cout << "GOLD SHOT\n";
			return shot_type::GOLD_SHOT;
		}
			

	/* Purple Shot */
	/* if angle is between 80 and 100 degrees (car is standing up) */
	} else if (abs(d.y) < 0.2f &&
			   ((sin(car.getRadAngle()) > 0.94f && d.x > 0) ||
			   (sin(car.getRadAngle()) < -0.94f && d.x < 0))) {
		
		this->applyShotEffect(shot_type::PURPLE_SHOT, d);
		std::cout << "PURPLE SHOT\n";
		return shot_type::PURPLE_SHOT;
	}

	std::cout << "NONE SHOT 2\n";
	return shot_type::NONE;
}

void Ball::reset(float x, float y) {
	this->unfreeze();
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

float Ball::getRadius() {
	return this->_radius;
}

void Ball::freeze() {
	this->ball->SetActive(false);
}


void Ball::unfreeze() {
	this->ball->SetActive(true);
}


Ball::~Ball() {}


