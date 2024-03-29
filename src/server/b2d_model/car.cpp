#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

#include "car.h"
#include <iostream>

#define CAR_WIDTH 4.0f
#define CAR_HEIGHT 1.5f
#define W_RADIUS 0.5f
#define CAR_DENSITY 1.0f
#define MOTOR_TORQUE 10.0f
#define MAX_MOTOR_SPEED 50.0f
#define ROTATION_SPEED 7 /* in radians */
#define FLIP_IMPULSE 40
#define JUMP_IMPULSE 60 /* in kg m/s (N * s) */
#define NITRO_IMPULSE 20
// #define NITRO_IMPULSE 20

#define TOL 0.1 /* 10cm tolerance */

#define FRONT_WH_X_POS(_x) _x + CAR_WIDTH - W_RADIUS - (CAR_WIDTH / 16)
#define REAR_WH_X_POS(_x) _x + W_RADIUS + (CAR_WIDTH / 16)
#define WH_Y_POS(_y) _y + W_RADIUS

#define CAR_GROUP_INDEX -8 /* for b2d filtering */


Car::Car(Car&& other) : d_jumpd(other.d_jumpd),
						flipped(other.flipped),
						_facing(other._facing),
						nitro_ptge(other.nitro_ptge),
						chassis(other.chassis), 
						rear_wh_bd(other.rear_wh_bd),
						rear_wh(other.rear_wh), 
						front_wh_bd(other.front_wh_bd),
						front_wh(other.front_wh) { 

	other.nitro_ptge = 0;
	other.chassis = nullptr;
	other.rear_wh_bd = nullptr;
	other.rear_wh = nullptr;
	other.front_wh_bd = nullptr;
	other.front_wh = nullptr;
}


Car& Car::operator=(Car&& other) {
	if (this == &other) {
		return *this;
	}
	this->d_jumpd = other.d_jumpd;
	this->flipped = other.flipped;
	this->_facing = other._facing;
	this->nitro_ptge = other.nitro_ptge;
	this->chassis = other.chassis;
	this->rear_wh_bd = other.rear_wh_bd;
	this->rear_wh = other.rear_wh;
	this->front_wh_bd = other.front_wh_bd;
	this->front_wh = other.front_wh;

	other.nitro_ptge = 0;
	other.chassis = nullptr;
	other.rear_wh_bd = nullptr;
	other.rear_wh = nullptr;
	other.front_wh_bd = nullptr;
	other.front_wh = nullptr;
	return *this;
}


Car::Car(b2World &world, float x_pos, float y_pos, facing f) : _facing(f) {
	set_chassis(world, x_pos, y_pos);
	set_wheels(world, x_pos, y_pos);
	
	b2Vec2 spring_axis(0.0f, W_RADIUS);
	b2WheelJointDef wheel_axis;

	/* 
		init rear wheel joint
	*/
	wheel_axis.Initialize(this->chassis, this->rear_wh_bd, 
						  this->rear_wh_bd->GetPosition(), spring_axis);

	float frec = 4.0f;
	float dampingRatio = 0.7f;
	float omega = 2.0f * b2_pi * frec;

	// mass_rearwh = mass_frontwh
	float mass_rearwh = this->rear_wh_bd->GetMass();

	wheel_axis.enableMotor = true;
	wheel_axis.motorSpeed = 0.0f;
	wheel_axis.maxMotorTorque = MOTOR_TORQUE;
	wheel_axis.stiffness = mass_rearwh * omega * omega;
	wheel_axis.damping = 2.0f * mass_rearwh * dampingRatio * omega;
	
	// shock limits
	wheel_axis.lowerTranslation = -0.0f;
	wheel_axis.upperTranslation = 0.0f;
	wheel_axis.enableLimit = true;

	this->rear_wh = (b2WheelJoint *) world.CreateJoint(&wheel_axis);


	/* 
		init front wheel joint
	*/
	wheel_axis.Initialize(this->chassis, this->front_wh_bd, 
						  this->front_wh_bd->GetPosition(), spring_axis);

	// the car will be rear wheel drive
	// wheel_axis.enableMotor = false;
	this->front_wh = (b2WheelJoint *) world.CreateJoint(&wheel_axis);
}


void Car::set_chassis(b2World &world, float x, float y) {
	b2BodyDef chassisDef;
	chassisDef.type = b2_dynamicBody;
	chassisDef.position.Set(x + CAR_WIDTH / 2, y + W_RADIUS + CAR_HEIGHT / 2);
	
	this->chassis = world.CreateBody(&chassisDef);
	
	// draw polygon
	b2PolygonShape skin;
	b2Vec2 vertices[8];
	vertices[0].Set(-CAR_WIDTH / 2, -CAR_HEIGHT / 2);
	vertices[1].Set(CAR_WIDTH / 2, -CAR_HEIGHT / 2);
	vertices[2].Set(CAR_WIDTH / 2, 0.0f);
	vertices[3].Set(CAR_WIDTH / 8, CAR_HEIGHT / 2);
	vertices[4].Set(-CAR_WIDTH / 8, CAR_HEIGHT / 2);
	vertices[5].Set(-CAR_WIDTH / 2, 0.0f);
	skin.Set(vertices, 6);
	
	// skin.SetAsBox(CAR_WIDTH / 2, CAR_HEIGHT / 2);
	
	b2FixtureDef skinFixture;
	skinFixture.shape = &skin;
	skinFixture.density = CAR_DENSITY;
	skinFixture.filter.groupIndex = CAR_GROUP_INDEX;
	
	this->chassis->CreateFixture(&skinFixture);
}


void Car::set_wheels(b2World &world, float x, float y) {
	b2CircleShape circle;
	circle.m_radius = W_RADIUS;
	
	b2FixtureDef fd;
	fd.filter.groupIndex = CAR_GROUP_INDEX;
	fd.shape = &circle;
	fd.density = CAR_DENSITY;
	fd.friction = 5.0f;

	b2BodyDef wheelDef;
	wheelDef.type = b2_dynamicBody;
	
	wheelDef.position.Set(REAR_WH_X_POS(x),
						  WH_Y_POS(y));
	this->rear_wh_bd = world.CreateBody(&wheelDef);
	this->rear_wh_bd->CreateFixture(&fd);

	wheelDef.position.Set(FRONT_WH_X_POS(x),
						  WH_Y_POS(y));
	this->front_wh_bd = world.CreateBody(&wheelDef);
	this->front_wh_bd->CreateFixture(&fd);
}


bool Car::touchingGround() {
	return this->rear_wh_bd->GetWorldCenter().y < W_RADIUS + TOL 
		|| this->front_wh_bd->GetWorldCenter().y < W_RADIUS + TOL;
}


/*    Actions    */

void Car::reset(float x, float y, facing f) {
	this->chassis->SetTransform(b2Vec2(x, y), 0);
	this->chassis->SetLinearVelocity(b2Vec2(0, 0));
	this->chassis->SetAngularVelocity(0);
	this->stop();
	this->_facing = f;
}


void Car::goLeft() {
	b2Vec2 i(-10.0f, 0);
	this->chassis->ApplyLinearImpulseToCenter(i, true);
	this->rear_wh->SetMotorSpeed(MAX_MOTOR_SPEED);
	this->front_wh->SetMotorSpeed(MAX_MOTOR_SPEED);
	this->_facing = facing::F_LEFT;
}

void Car::goRight() {
	b2Vec2 i(10.0f, 0);
	this->chassis->ApplyLinearImpulseToCenter(i, true);
	this->rear_wh->SetMotorSpeed(-MAX_MOTOR_SPEED);
	this->front_wh->SetMotorSpeed(-MAX_MOTOR_SPEED);
	this->_facing = facing::F_RIGHT;
}

void Car::stop() {
	this->rear_wh->SetMotorSpeed(0.0f);
	this->front_wh->SetMotorSpeed(0.0f);
}

void Car::rotateDown() {
	// if (this->_facing == facing::F_RIGHT) {
	if (this->rear_wh_bd->GetWorldCenter().y < W_RADIUS + TOL ||
		this->front_wh_bd->GetWorldCenter().y < W_RADIUS + TOL) {
			return;
	}
	this->chassis->SetAngularVelocity(ROTATION_SPEED);
}

void Car::rotateUp() {
	// if (this->_facing == facing::F_RIGHT) {
	if (this->rear_wh_bd->GetWorldCenter().y < W_RADIUS + TOL ||
		this->front_wh_bd->GetWorldCenter().y < W_RADIUS + TOL) {
			return;
	}
	this->chassis->SetAngularVelocity(-ROTATION_SPEED);
}


void Car::stopRotation() {
	this->chassis->SetAngularVelocity(0);
}


void Car::triggerNitro() {
	if (nitro_ptge < 5) {
		return;
	}
	float rad_angle = this->chassis->GetAngle();
	b2Vec2 i(cos(-rad_angle), sin(rad_angle));
	i *= this->_facing == facing::F_LEFT ? -NITRO_IMPULSE : NITRO_IMPULSE ;
	
	// this->chassis->ApplyLinearImpulseToCenter(i, true);
	this->chassis->SetLinearVelocity(i);
	this->nitro_ptge -= 1;
	this->nitro_trigg = true;
}

void Car::releaseNitro() {
	this->chassis->SetLinearVelocity(b2Vec2(0, 0));
	this->nitro_trigg = false;
}

void Car::nitroRefill() {
	this->nitro_ptge += this->nitro_ptge < 100 ? 10 : 0;
}

void Car::jump() {
	// in the ground
	if (this->touchingGround()) {
		this->d_jumpd = false;
		this->jumpd = false;
	
	// in the air but not double jumped nor flipped
	} else if (this->flipped || this->d_jumpd) {
		return;
	}

	// if the car has significative angular velocity,
	// performs a flip, i.e. increase angular velocity
	if (abs(this->chassis->GetAngularVelocity()) > 3) {
      	float a_impulse = FLIP_IMPULSE * this->chassis->GetAngularVelocity();
		this->chassis->ApplyAngularImpulse(a_impulse, true);
		
		b2Vec2 l_impulse(this->_facing == facing::F_LEFT ? -1 : 1, 0);
		l_impulse *= FLIP_IMPULSE;
		this->chassis->ApplyLinearImpulseToCenter(l_impulse, true);

		this->flipped = true;
	
	/* First or double jump */
	} else {
		this->flipped = false;

		if (this->jumpd) {
			this->d_jumpd = true;
		
		} else {
			this->jumpd = true;
		}

		// performs an impulse perpendicular to the body (locally)
		float rad_angle = this->chassis->GetAngle();
		b2Vec2 i(sin(-rad_angle), cos(-rad_angle));
		i *= JUMP_IMPULSE;
		
		// if (this->flipped && this->_facing == facing::F_RIGHT) {
		// 	i = b2Vec2(-i.x, i.y);
		// }
		// b2Vec2 i(0, JUMP_IMPULSE);
		this->chassis->ApplyLinearImpulseToCenter(i, true);
	}
}


/*    Stats    */

b2Vec2 Car::getPosition() {
	return this->chassis->GetPosition() - b2Vec2(0, W_RADIUS);
}

float Car::getAngle() {
	uint16_t deg_angle = (uint16_t) abs(this->chassis->GetAngle() * 180.0f / b2_pi + 360.0f);
	return deg_angle % 360;
}

float Car::getRadAngle() {
	return this->chassis->GetAngle();
}

facing Car::getFacing() {
	return this->_facing;
}

b2Vec2 Car::getVelocity() {
	return this->chassis->GetLinearVelocity();
}

bool Car::hasFlipped() {
	if (this->flipped) {
		this->flipped = false;
		return true;
	}
	return false;
}

bool Car::isPointingTo(const b2Vec2 &coord) {
	b2Vec2 d = coord - this->chassis->GetPosition();

	if (d.x < 0) {
		return this->_facing == facing::F_LEFT;
	}
	return this->_facing == facing::F_RIGHT;
}


bool Car::nitroTriggered() {
	return this->nitro_trigg;
}

uint8_t Car::remainingNitro() {
	return this->nitro_ptge;
}

void Car::removeFromWorld(b2World &w) {
	w.DestroyBody(this->chassis);
	w.DestroyBody(this->rear_wh_bd);
	w.DestroyBody(this->front_wh_bd);
}

bool Car::hasJumped() {
	if (this->jumpd && 
		this->touchingGround() && 
		this->chassis->GetLinearVelocity().y < 0) {
		
		this->jumpd = false;
		// return true;
	}
	return this->jumpd;
}

bool Car::hasDJumped() {
	if (this->d_jumpd && this->touchingGround()) {
		this->d_jumpd = false;
		return true;
	}
	return this->d_jumpd;
}

Car::~Car() {
}
