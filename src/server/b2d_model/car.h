#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

class Car{
	private:
	bool d_jumpd = false;
	b2Body *chassis;

	b2Body *rear_wh_bd;
	b2WheelJoint* rear_wh;

	b2Body *front_wh_bd;
	b2WheelJoint* front_wh;

	void set_wheels(b2World &world, float x, float y);
	void set_chassis(b2World &world, float x, float y);

	public:
	Car(b2World &world, float x_pos, float y_pos);
	
	/* Actions */
	void goForward();
	void goBackward();
	void stop();
	void jump();
	void rotateLeft();
	void rotateRight();

	/* Stats */
	b2Vec2 getPosition();
	float getAngle(); /* in degrees */
	float getSpeed();

	~Car();
};
