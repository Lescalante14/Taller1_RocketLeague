#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <ctime>

#include "thread_match_handler.h"
#include "common/queue_empty_exception.h"
#include "server/b2d_model/game_model.h"

#define STEP_FREQ 1 / 50e-6 /* 20kHz (every 50us) */
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
			if (clock() - now >= STEP_TICK_FREQ) {
				now = clock();
				game_model.step();
				// std::cout << "Ball position x: " << game_model.getState().get_ball_position_x();
				// std::cout << ", Ball position y: " << game_model.getState().get_ball_position_y();
				// std::cout << std::endl;
				this->match.push_to_output_queues(game_model.getState());
			}
            UserAction action = input_queue.pop();
            game_model.updateGame(action);			
			// std::cout << unsigned(action.get_car_id()) << " " << action.is(UP_PUSH) << std::endl;

        } catch(const QueueEmptyException& err) {
            // std::cout << "vacíaaaaaaa" << std::endl;
            usleep(1000);
        }
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