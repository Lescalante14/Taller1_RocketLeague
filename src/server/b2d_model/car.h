#ifndef B2_CAR_H
#define B2_CAR_H

#include <stdint.h>
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>
#include <box2d/b2_wheel_joint.h>

enum facing {F_LEFT, F_RIGHT};

class Car{
	private:
	bool d_jumpd = false;
	bool flipped = false;
	bool nitro_trigg = false;
	facing _facing;

	uint8_t nitro_ptge = 100;
	b2Body *chassis = nullptr;

	b2Body *rear_wh_bd = nullptr;
	b2WheelJoint *rear_wh = nullptr;

	b2Body *front_wh_bd = nullptr;
	b2WheelJoint *front_wh = nullptr;

	void set_wheels(b2World &world, float x, float y);
	void set_chassis(b2World &world, float x, float y);

	public:
	Car(b2World &world, float x_pos, float y_pos, facing f);
	
	Car(const Car&) = delete;
	Car& operator=(const Car&) = delete;

	Car(Car&&);
	Car& operator=(Car&&);

	/* Actions */
	void goLeft();
	void goRight();
	void stop();
	void triggerNitro();
	void releaseNitro();
	void nitroRefill();
	void jump();
	void rotateDown();
	void rotateUp();

	/* Stats */
	b2Vec2 getPosition();
	b2Vec2 getVelocity();
	float getAngle(); /* in degrees */
	facing getFacing();
	bool hasFlipped();
	bool nitroTriggered();
	uint8_t remainingNitro();
	bool isPointingTo(const b2Vec2 &coord);

	~Car();
};

#endif
