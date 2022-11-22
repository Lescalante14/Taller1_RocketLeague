#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

#include "car.h"

#define CAR_WIDTH 3.0f
#define CAR_HEIGHT 1.5f
#define W_RADIUS 0.25f
#define CAR_DENSITY 1.0f
#define MOTOR_TORQUE 10.0f
#define MAX_MOTOR_SPEED 50.0f
#define FLIP_SPEED 5 /* in radians */
#define JUMP_IMPULSE 60 /* in kg m/s (N * s) */
#define NITRO_IMPULSE 20

#define FRONT_WH_X_POS(_x) _x - 2 * W_RADIUS + CAR_WIDTH / 2
#define REAR_WH_X_POS(_x) _x + 2 * W_RADIUS - CAR_WIDTH / 2
#define WH_Y_POS(_y) _y + W_RADIUS - CAR_HEIGHT / 2


Car::Car(Car&& other) : d_jumpd(other.d_jumpd),
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


Car::Car(b2World &world, float x_pos, float y_pos) {
	set_chassis(world, x_pos, y_pos);
	set_wheels(world, x_pos, y_pos);
	
	b2Vec2 spring_axis(0.0f, 1.0f);
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
	wheel_axis.maxMotorTorque = 10.0f;
	wheel_axis.stiffness = mass_rearwh * omega * omega;
	wheel_axis.damping = 2.0f * mass_rearwh * dampingRatio * omega;
	
	// shock limits
	wheel_axis.lowerTranslation = -0.25f;
	wheel_axis.upperTranslation = 0.25f;
	wheel_axis.enableLimit = true;

	this->rear_wh = (b2WheelJoint *) world.CreateJoint(&wheel_axis);


	/* 
		init front wheel joint
	*/
	wheel_axis.Initialize(this->chassis, this->front_wh_bd, 
						  this->front_wh_bd->GetPosition(), spring_axis);

	// the car will be rear wheel drive
	wheel_axis.enableMotor = false;
	this->front_wh = (b2WheelJoint *) world.CreateJoint(&wheel_axis);
}


void Car::set_chassis(b2World &world, float x, float y) {
	b2BodyDef chassisDef;
	chassisDef.type = b2_dynamicBody;
	chassisDef.position.Set(x, y + W_RADIUS);
	
	this->chassis = world.CreateBody(&chassisDef);
	
	b2PolygonShape skin;
	skin.SetAsBox(CAR_WIDTH / 2, CAR_HEIGHT / 2);

	this->chassis->CreateFixture(&skin, CAR_DENSITY);
}


void Car::set_wheels(b2World &world, float x, float y) {
	b2CircleShape circle;
	circle.m_radius = W_RADIUS;
	
	b2FixtureDef fd;
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
}

void Car::goRight() {
	this->rear_wh->SetMotorSpeed(-MAX_MOTOR_SPEED);
}

void Car::stop() {
	this->rear_wh->SetMotorSpeed(0.0f);
}

void Car::rotateCCW() {
	this->chassis->SetAngularVelocity(FLIP_SPEED);
}

void Car::rotateCW() {
	this->chassis->SetAngularVelocity(-FLIP_SPEED);
}

void Car::nitro() {
	if (nitro_ptge < 10) {
		return;
	}

	b2Vec2 i = this->chassis->GetLinearVelocity();
	i *= NITRO_IMPULSE / i.Length();
	this->chassis->ApplyLinearImpulse(i, this->chassis->GetWorldCenter(), true);
	nitro_ptge -= 10;
}


void Car::nitroRefill() {
	this->nitro_ptge = 100;
}


void Car::jump() {
	// is in the ground
	if (this->chassis->GetWorldCenter().y == W_RADIUS) {
		this->d_jumpd = false;
	
	// in the air and not double jumped
	} else if (!this->d_jumpd) {
		this->d_jumpd = true;
	
	} else {
		return;
	}

	// if the car has significative angular velocity,
	// performs a flip, i.e. increase angular velocity
	if (abs(this->chassis->GetAngularVelocity()) > 3) {
      	this->chassis->ApplyAngularImpulse(10 * this->chassis->GetAngularVelocity(),
							    		   true);
	}
	// performs the upward impulse
	float rad_angle = this->chassis->GetAngle();
	b2Vec2 i(sin(-rad_angle), cos(-rad_angle));
	i *= JUMP_IMPULSE;
	this->chassis->ApplyLinearImpulse(i, this->chassis->GetWorldCenter(), true);
}


/*    Stats    */

b2Vec2 Car::getPosition() {
	return this->chassis->GetPosition();
}

float Car::getAngle() {
	return this->chassis->GetAngle();
}

float Car::getSpeed() {
	return this->chassis->GetLinearVelocity().Length();
}


Car::~Car() {}
