#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <ctime>

#include "thread_match_handler.h"
#include "common/queue_empty_exception.h"
#include "server/b2d_model/game_model.h"

#define STEP_FREQ 0.06f /* in kHz */
#define UPDATE_FREQ 0.6f /* in kHz */

#define MILI2MICRO(t) (t) * 1e3
#define KHZ2HZ(f) (f) * 1e3

ThreadMatchHandler::ThreadMatchHandler(
    LobbyMatch& _match
): match(_match) { }


void ThreadMatchHandler::run() {
    BlockingQueue<UserAction>& input_queue = *(this->match.get_match_input_queue());
	GameModel game_model(this->match.get_size(), (size_t) round(KHZ2HZ(STEP_FREQ)));
	this->match.push_to_output_queues(game_model.getSetup());
	this->match.push_to_output_queues(game_model.getState());

	float update_iter = 0;

    while (!game_model.finished()) {
		try {
			UserAction action = input_queue.try_pop();
			game_model.updateGame(action);			

		} catch(const QueueEmptyException& err) {}

		// UPDATE_FREQ * k = STEP_FREQ --> every k updates, perform a step. 
		if (update_iter++ > UPDATE_FREQ / STEP_FREQ) {
			update_iter = 0;
			game_model.step();
			this->match.push_to_output_queues(game_model.getState());
		}

		usleep(MILI2MICRO(1 / UPDATE_FREQ));
    }
}