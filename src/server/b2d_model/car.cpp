#include "car.h"
#include "box2d/b2_wheel_joint.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"

#define CAR_WIDTH 3.0f
#define CAR_HEIGHT 1.5f
#define W_RADIUS 0.25f
#define DENSITY 1.0f
#define MOTOR_TORQUE 10.0f
#define MAX_MOTOR_SPEED 50.0f
#define FLIP_SPEED 5 /* in radians */

#define FRONT_WH_X_POS(_x) _x - 2 * W_RADIUS + CAR_WIDTH / 2
#define REAR_WH_X_POS(_x) _x + 2 * W_RADIUS - CAR_WIDTH / 2
#define WH_Y_POS(_y) _y + W_RADIUS - CAR_HEIGHT / 2


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


void Car::set_wheels(b2World &world, float x, float y) {
	b2CircleShape circle;
	circle.m_radius = W_RADIUS;
	
	b2FixtureDef fd;
	fd.shape = &circle;
	fd.density = DENSITY;
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


void Car::set_chassis(b2World &world, float x, float y) {
	b2BodyDef chassisDef;
	chassisDef.type = b2_dynamicBody;
	chassisDef.position.Set(x, y + W_RADIUS);
	
	this->chassis = world.CreateBody(&chassisDef);
	
	b2PolygonShape skin;
	skin.SetAsBox(CAR_WIDTH / 2, CAR_HEIGHT / 2);

	this->chassis->CreateFixture(&skin, DENSITY);
}

/*    Actions    */

void Car::goForward() {
	this->rear_wh->SetMotorSpeed(MAX_MOTOR_SPEED);
}

void Car::goBackward() {
	this->rear_wh->SetMotorSpeed(-MAX_MOTOR_SPEED);
}

void Car::stop() {
	this->rear_wh->SetMotorSpeed(0.0f);
}

void Car::rotateLeft() {
	this->chassis->SetAngularVelocity(FLIP_SPEED);
}

void Car::rotateRight() {
	this->chassis->SetAngularVelocity(-FLIP_SPEED);
}

void Car::jump() {

	if (this->chassis->GetWorldCenter().y == W_RADIUS) {
		this->d_jumpd = false;
	
	} else if (this->d_jumpd) {
		return;
	}

	// if the car has significative angular velocity,
	// performs a flip, i.e. increase angular velocity
	if (abs(this->chassis->GetAngularVelocity()) > 3) {
      	this->chassis->ApplyAngularImpulse(10 * this->chassis->GetAngularVelocity(),
							    		   true);

	}
	// performs the upward impulse
	this->chassis->ApplyLinearImpulse(b2Vec2(0, 60),
						  			  this->chassis->GetWorldCenter(),
						  			  true);
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
