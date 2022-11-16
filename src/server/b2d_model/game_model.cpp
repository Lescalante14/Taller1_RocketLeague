#include "game_model.h"
#define TIME_STEP 1.0f / 60.0f
#define VEL_ITER 6
#define POS_ITER 2

GameModel::GameModel() : world(b2Vec2(0.0f, -10.0f)) {

}

void GameModel::updateGame(MatchState &s) {
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
	devuelvo
}

GameModel::~GameModel() {}
