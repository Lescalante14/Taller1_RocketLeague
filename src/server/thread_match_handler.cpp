#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <ctime>

#include "thread_match_handler.h"
#include "common/queue_empty_exception.h"
#include "server/b2d_model/game_model.h"

#define STEP_FREQ 1 / 10e-6 /* 100kHz (every 10us) */
#define STEP_TICK_FREQ 3e9 / (STEP_FREQ) /* in cpu ticks */

ThreadMatchHandler::ThreadMatchHandler(
    LobbyMatch& _match
): match(_match) { }


void ThreadMatchHandler::run() {
    NonBlockingQueue<UserAction>& input_queue = *(this->match.get_match_input_queue());
	GameModel game_model(this->match.get_size(), STEP_FREQ);
	this->match.push_to_output_queues(game_model.getSetup());
	this->match.push_to_output_queues(game_model.getState());

	clock_t now = clock();

    while (1) {
        try {
            UserAction action = input_queue.pop();
            game_model.updateGame(action);			

        } catch(const QueueEmptyException& err) {
		}
		if (clock() - now >= 25000) {
			now = clock();
			game_model.step();
			std::cout << "Car position x: " << game_model.getState().get_cars().at(0).get_position_x();
			std::cout << ", Car position y: " << game_model.getState().get_cars().at(0).get_position_y();
			std::cout << std::endl;
			this->match.push_to_output_queues(game_model.getState());
		}
			// std::cout << unsigned(action.get_car_id()) << " " << action.is(UP_PUSH) << std::endl;

            // std::cout << "vacíaaaaaaa" << std::endl;
            // usleep(1000);
    }
    

    // Acá se haría el loop

    // UserAction action = input_queue.pop();
    // action.is(UP_PUSH);
    // action.get_car_id();

    //  acá va la logica del partido (box2d)

    
    // acá se pushea el estado actuaizado a todos los outputs queues
    // std::for_each(
    //     this->match.begin(), 
    //     this->match_handlers.end(), 
    //     [] (ThreadMatchHandler* handler) { 
    //         handler->join();
    //         delete handler;
    //         return true;
    //     });
}