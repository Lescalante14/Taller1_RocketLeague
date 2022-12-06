#ifndef B2D_GAME_MODEL_H
#define B2D_GAME_MODEL_H

#include <box2d/box2d.h>
#include <stdint.h>

#include <vector>
#include <queue>
#include <map>

#include "common/match_state.h"
#include "common/match_setup.h"
#include "common/user_action.h"
#include "car.h"
#include "ball.h"


class GameModel { 
	private:
	b2World world;
	uint16_t timer = 0; // in seconds
	size_t step_freq = 0;
	size_t step_count = 0;
	size_t sleep_count = 0;

	float height = 0;
	float length = 0;
	float scorer_height = 0;
	shot_type last_shot = shot_type::NONE;

	uint8_t l_scorer = 0;
	uint8_t r_scorer = 0;
	bool scored = false;

	std::map<uint8_t, Car> cars;
	Ball ball;
	
	std::queue<MatchState> last_states;

	void saveState();
	void setLimits();
	bool isInsideLScorer(const b2Vec2 &pos);
	bool isInsideRScorer(const b2Vec2 &pos);
	void resetCars();

	public:
	/* step frep is in Hz */
	GameModel(size_t cars_amount, size_t _step_freq);
	void step();
	void updateGame(UserAction &a);
	MatchState getState();
	MatchSetup getSetup();
	bool finished();
	~GameModel();
};

#endif
