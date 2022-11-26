#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

#include "car.h"

#define CAR_WIDTH 4.0f
#define CAR_HEIGHT 1.5f
#define W_RADIUS 0.5f
#define CAR_DENSITY 2.0f
#define MOTOR_TORQUE 20.0f
#define MAX_MOTOR_SPEED 100.0f
#define ROTATION_SPEED 5 /* in radians */
#define FLIP_IMPULSE 10
#define JUMP_IMPULSE 60 /* in kg m/s (N * s) */
#define NITRO_IMPULSE 20

#define FRONT_WH_X_POS(_x) _x + CAR_WIDTH - W_RADIUS
#define REAR_WH_X_POS(_x) _x + W_RADIUS
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
	skin.SetAsBox(CAR_WIDTH / 2, CAR_HEIGHT / 2);
	
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
	fd.friction = 0.9f;

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


/*    Actions    */

void Car::goLeft() {
	this->rear_wh->SetMotorSpeed(MAX_MOTOR_SPEED);
	this->front_wh->SetMotorSpeed(MAX_MOTOR_SPEED);
	this->_facing = facing::F_LEFT;
}

void Car::goRight() {
	this->rear_wh->SetMotorSpeed(-MAX_MOTOR_SPEED);
	this->front_wh->SetMotorSpeed(-MAX_MOTOR_SPEED);
	this->_facing = facing::F_RIGHT;
}

void Car::stop() {
	this->rear_wh->SetMotorSpeed(0.0f);
}

void Car::rotateCCW() {
	this->chassis->SetAngularVelocity(ROTATION_SPEED);
}

void Car::rotateCW() {
	this->chassis->SetAngularVelocity(-ROTATION_SPEED);
}

void Car::triggerNitro() {
	if (nitro_ptge < 10) {
		return;
	}
	float rad_angle = this->chassis->GetAngle();
	b2Vec2 i(cos(-rad_angle), sin(-rad_angle));
	i *= this->_facing == facing::F_RIGHT ? NITRO_IMPULSE : -NITRO_IMPULSE;

	this->chassis->ApplyLinearImpulse(i, this->chassis->GetWorldCenter(), true);
	this->nitro_ptge -= 10;
	this->nitro_trigg = true;
}

void Car::releaseNitro() {
	this->nitro_trigg = false;
}

void Car::nitroRefill() {
	this->nitro_ptge = 100;
}

void Car::jump() {
	// in the ground
	if (this->rear_wh_bd->GetWorldCenter().y == W_RADIUS ||
		this->front_wh_bd->GetWorldCenter().y == W_RADIUS) {
		this->d_jumpd = false;
	
	// in the air but not double jumped
	} else if (!this->d_jumpd) {
		this->d_jumpd = true;
	
	} else {
		return;
	}
	// if the car has significative angular velocity,
	// performs a flip, i.e. increase angular velocity
	if (abs(this->chassis->GetAngularVelocity()) > 3) {
      	float new_a_vel = FLIP_IMPULSE * this->chassis->GetAngularVelocity();
		this->chassis->ApplyAngularImpulse(new_a_vel, true);
		this->flipped = true;
	
	} else {
		this->flipped = false;
	}

	// performs an impulse perpendicular to the body (locally)
	float rad_angle = this->chassis->GetAngle();
	b2Vec2 i(sin(-rad_angle), cos(-rad_angle));
	i *= JUMP_IMPULSE;
	this->chassis->ApplyLinearImpulseToCenter(i, true);
}


/*    Stats    */

b2Vec2 Car::getPosition() {
	return this->chassis->GetPosition() - b2Vec2(0, W_RADIUS);
}

float Car::getAngle() {
	uint16_t deg_angle = (uint16_t) abs(this->chassis->GetAngle() * 180.0f / b2_pi + 360.0f);
	return deg_angle % 360;
}

facing Car::getFacing() {
	return this->_facing;
}

b2Vec2 Car::getVelocity() {
	return this->chassis->GetLinearVelocity();
}

bool Car::hasFlipped() {
	return this->flipped;
}

bool Car::isPointingTo(const b2Vec2 &coord) {
	b2Vec2 d = coord - this->chassis->GetPosition();

	if (d.y < 0) {
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


Car::~Car() {}
