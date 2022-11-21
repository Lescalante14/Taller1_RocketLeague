#include <yaml.h>
#include "game_model.h"

#define TIME_STEP 1.0f / 60.0f
#define VEL_ITER 6
#define POS_ITER 2

#define CAMP_HEIGHT 20.0f
#define CAMP_LENGTH 40.0f
#define CAR_XPOS_OFFSET 2.0f

#define WALL_THICKNESS 10.0f
#define MAX_CARS 4


GameModel::GameModel(uint8_t cars_amount) : world(b2Vec2(0.0f, -10.0f)) {
	YAML::Node config = YAML::LoadFile(".config.yaml");	
	int xcar_offset = 0;

	for (int id = 0; id < cars_amount; id++) {
		if (id % 2) {
			xcar_offset += CAR_XPOS_OFFSET;
		} else {
			xcar_offset = CAMP_LENGTH - xcar_offset;
		}
		this->cars.emplace(id, &(this->world), xcar_offset, 0);
	}

	this->ball = Ball(&world, 
					  config["camp_length"].as<int>() / 2, 
					  config["camp_height"].as<int>() / 2);

	this->setLimits(config["length"].as<int>(),
					config["height"].as<int>());

}


void GameModel::setLimits(int height, int length) {
	b2BodyDef bdef;
	bdef.type = b2_staticBody;
	
	/* floor */
	bdef.position.Set(length / 2.0f, -WALL_THICKNESS / 2.0f);
	b2Body *floor = this->world.CreateBody(&bdef);
	b2PolygonShape _floor;
	_floor.SetAsBox(length / 2.0f, WALL_THICKNESS / 2.0f);
	floor->CreateFixture(&_floor, 0.0f);

	/* seeling */
	bdef.position.Set(length / 2.0f, (float) height + WALL_THICKNESS / 2.0f);
	b2Body *seeling = this->world.CreateBody(&bdef);
	b2PolygonShape _seeling;
	_seeling.SetAsBox(length / 2.0f, WALL_THICKNESS / 2.0f);
	seeling->CreateFixture(&_seeling, 0.0f);

	/* left wall */
	bdef.position.Set(-WALL_THICKNESS / 2.0f, height / 2.0f);
	b2Body *left_wall = this->world.CreateBody(&bdef);
	b2PolygonShape _left_wall;
	_left_wall.SetAsBox(WALL_THICKNESS / 2.0f, height / 2.0f);
	left_wall->CreateFixture(&_left_wall, 0.0f);

	/* right wall */
	bdef.position.Set((float) length + WALL_THICKNESS / 2.0f, height / 2.0f);
	b2Body *right_wall = this->world.CreateBody(&bdef);
	b2PolygonShape _right_wall;
	_right_wall.SetAsBox(WALL_THICKNESS / 2.0f, height / 2.0f);
	right_wall->CreateFixture(&_right_wall, 0.0f);
}


void GameModel::updateGame(UserAction &a) {
	/*
		llamo al protocolo para resolver los movs,
		y los aplico.
		matchstate pasado con std::move
	*/
}


void GameModel::step() {
	this->world.Step(TIME_STEP, VEL_ITER, POS_ITER);
}


MatchState GameModel::getState() {
}

GameModel::~GameModel() {}
