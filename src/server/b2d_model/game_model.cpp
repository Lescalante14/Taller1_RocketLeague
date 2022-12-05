#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>

#include "game_model.h"
#include "common/car_state.h"

#define TIME_STEP 1.0f / 60.0f
#define VEL_ITER 6
#define POS_ITER 2

#define CAMP_HEIGHT 20.0f
#define CAMP_LENGTH 40.0f
#define CAR_XPOS_OFFSET 3.0f
#define CAR_YPOS_OFFSET 3.0f

#define WALL_THICKNESS 10.0f
#define SCORER_WIDTH 2.0f
#define SCORER_HEIGHT 8

#define MAX_CARS 4

#define NITRO_REFILL_FREQ 5 /* in seconds */

#define GRAVITY 10.0f
#define FLOOR_FRICTION 5.0f

#define DEFAULT_TIME 150 /* in seconds */


GameModel::GameModel(size_t cars_amount, size_t _step_freq) 
			: world(b2Vec2(0.0f, -GRAVITY)),
			  step_freq(_step_freq),
			  ball(this->world, 0, 0, ball_size::MED_BALL) {
	
	YAML::Node config = YAML::LoadFile(".rl_config.yml");	

	this->length = config["camp_length"].as<float>();
	this->height = config["camp_height"].as<float>();
	this->setLimits();
	
	this->ball.move(this->length / 2, this->height / 2);
	this->ball.resize((ball_size) config["ball_size"].as<int>());

	int xcar_offset = 0;

	for (uint8_t id = 0; id < cars_amount; id++) {
		facing f = facing::F_RIGHT;

		if (id % 2) {
			xcar_offset = this->length - xcar_offset - 4.0f;
			f = facing::F_LEFT;

		} else {
			xcar_offset += CAR_XPOS_OFFSET;
		}

		this->cars.emplace(id, Car(this->world,
								   xcar_offset,
								   CAR_YPOS_OFFSET,
							       f));
	}
	this->scorer_height = SCORER_HEIGHT;

	if (config["scorer_height"].as<float>() <= this->height) {
		this->scorer_height = config["scorer_height"].as<float>();
	}
	this->timer = DEFAULT_TIME;
	
	if (config["match_duration"].as<size_t>() <= 300) {
		this->timer = config["match_duration"].as<uint16_t>();
	}
}


void GameModel::setLimits() {
	b2BodyDef bdef;
	bdef.type = b2_staticBody;
	
	/* floor */
	bdef.position.Set(this->length / 2.0f, -WALL_THICKNESS / 2.0f);
	b2Body *floor = this->world.CreateBody(&bdef);
	b2PolygonShape _floor;
	_floor.SetAsBox(this->length / 2.0f, WALL_THICKNESS / 2.0f);
	floor->CreateFixture(&_floor, 0.0f)->SetFriction(FLOOR_FRICTION);

	/* seeling */
	bdef.position.Set(this->length / 2.0f, (float) this->height + WALL_THICKNESS / 2.0f);
	b2Body *seeling = this->world.CreateBody(&bdef);
	b2PolygonShape _seeling;
	_seeling.SetAsBox(this->length / 2.0f, WALL_THICKNESS / 2.0f);
	seeling->CreateFixture(&_seeling, 0.0f);

	/* left wall */
	bdef.position.Set(-WALL_THICKNESS / 2.0f, this->height / 2.0f);
	b2Body *left_wall = this->world.CreateBody(&bdef);
	b2PolygonShape _left_wall;
	_left_wall.SetAsBox(WALL_THICKNESS / 2.0f, this->height / 2.0f);
	left_wall->CreateFixture(&_left_wall, 0.0f);

	/* right wall */
	bdef.position.Set((float) this->length + WALL_THICKNESS / 2.0f, this->height / 2.0f);
	b2Body *right_wall = this->world.CreateBody(&bdef);
	b2PolygonShape _right_wall;
	_right_wall.SetAsBox(WALL_THICKNESS / 2.0f, this->height / 2.0f);
	right_wall->CreateFixture(&_right_wall, 0.0f);
}


bool GameModel::isInsideLScorer(const b2Vec2 &pos) {
	return pos.x < SCORER_WIDTH && pos.y < this->scorer_height;
}

bool GameModel::isInsideRScorer(const b2Vec2 &pos) {
	return pos.x > this->length - SCORER_WIDTH && pos.y < this->scorer_height;
}


void GameModel::resetCars() {
	int xcar_offset = 0;
	size_t cars_amount = this->cars.size();

	for (uint8_t id = 0; id < cars_amount; id++) {
		facing f = facing::F_RIGHT;

		if (id % 2) {
			xcar_offset = this->length - xcar_offset - 4.0f;
			f = facing::F_LEFT;

		} else {
			xcar_offset += CAR_XPOS_OFFSET;
		}
		this->cars.at(id).removeFromWorld(this->world);
		this->cars.erase(id);
		this->cars.emplace(id, Car(this->world,
								   xcar_offset,
								   CAR_YPOS_OFFSET,
							       f));
		// this->cars.at(id).reset(xcar_offset, CAR_YPOS_OFFSET, f);
	}
}


void GameModel::updateGame(UserAction &a) {
	uint8_t id = a.get_car_id();
	Car &car = this->cars.at(id);

	if (a.is(LEFT_PUSH)) {
		car.goLeft();

	} else if (a.is(RIGHT_RELEASE) || a.is(LEFT_RELEASE)) {
		car.stop();
	
	} else if (a.is(RIGHT_PUSH)) {
		car.goRight();

	} else if (a.is(UP_RELEASE) || a.is(DOWN_RELEASE)) {
		car.stopRotation();

	} else if (a.is(UP_PUSH)) {
		car.rotateUp();

	} else if (a.is(DOWN_PUSH)) {
		car.rotateDown();

	} else if (a.is(JUMP)) {
		car.jump();	

		if (this->last_shot == shot_type::NONE) {
			std::cout << "PERFORMING FLIP...\n";
			this->last_shot = this->ball.applyShotEffect(car);
		}

	} else if (a.is(NITRO_PUSH)) {
		car.triggerNitro();
	
	} else if (a.is(NITRO_RELEASE)) {
		car.releaseNitro();
	}
}


void GameModel::step() {
	if (!timer) {
		return;
	}

	for (auto it = this->cars.begin(); it != this->cars.end(); ++it) {
		if (it->second.nitroTriggered() && it->second.remainingNitro()) {
			it->second.triggerNitro();
		
		} else if (!(timer % NITRO_REFILL_FREQ)) {
			it->second.nitroRefill();
		}
	}

	if (this->isInsideLScorer(this->ball.getPosition())) {
		this->r_scorer++;
		this->ball.reset(this->length / 2, this->height / 2);
		this->resetCars();

	} else if (this->isInsideRScorer(this->ball.getPosition())) {
		this->l_scorer++;
		this->ball.reset(this->length / 2, this->height / 2);
		this->resetCars();
	}


	this->world.Step(TIME_STEP, VEL_ITER, POS_ITER);
	this->last_shot = shot_type::NONE;
	this->step_count++;

	if (!(this->step_count % this->step_freq)) {
		this->timer--;
	}
}


MatchState GameModel::getState() {
	std::vector<CarState> car_states;
	
	for (auto it = this->cars.begin(); it != this->cars.end(); ++it) {
		Car &c = it->second;
		car_states.emplace_back(it->first, 
								c.nitroTriggered(),
								c.remainingNitro(),
								c.getFacing(),
								c.getAngle() , 
								c.getPosition().x,
								c.getPosition().y);
	}

	BallState b_state(this->ball.getPosition().x, this->ball.getPosition().y,
					  this->ball.getAngle(), this->last_shot);

	return MatchState(this->timer, this->timer,
					  this->l_scorer, this->r_scorer, cars.size(),
					  b_state, car_states);
}


MatchSetup GameModel::getSetup() {
	return MatchSetup((float) this->length, (float) this->height,
					  (float) this->scorer_height, this->ball.getRadius(),
					  4, this->cars.size());
}


GameModel::~GameModel() {}
