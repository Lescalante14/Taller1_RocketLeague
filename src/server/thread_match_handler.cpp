#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <ctime>

#include "thread_match_handler.h"
#include "common/queue_empty_exception.h"
#include "server/b2d_model/game_model.h"

#define STEP_FREQ 0.06f /* in kHz */
#define UPDATE_FREQ 0.6f /* in kHz */

#define MILI2MICRO(t) (t * 1e3)
#define KHZ2HZ(f) (f * 1e3)

ThreadMatchHandler::ThreadMatchHandler(
    LobbyMatch& _match
): match(_match) { }


void ThreadMatchHandler::run() {
    NonBlockingQueue<UserAction>& input_queue = *(this->match.get_match_input_queue());
	GameModel game_model(this->match.get_size(), KHZ2HZ(STEP_FREQ));
	this->match.push_to_output_queues(game_model.getSetup());
	this->match.push_to_output_queues(game_model.getState());

	float update_iter = 0;

    while (1) {
		try {
			UserAction action = input_queue.pop();
			game_model.updateGame(action);			

		} catch(const QueueEmptyException& err) {}

		// UPDATE_FREQ * k = STEP_FREQ --> every k updates, perform a step. 
		if (update_iter++ > UPDATE_FREQ / STEP_FREQ) {
			update_iter = 0;

			game_model.step();
			this->match.push_to_output_queues(game_model.getState());
			

			// std::cout << "Car 2 position x: " << game_model.getState().get_cars().at(1).get_position_x();
			// std::cout << ", Car 2 position y: " << game_model.getState().get_cars().at(1).get_position_y();
			// std::cout << std::endl;
		}

                // Nota: recordar q este loop es en escencia igual q el loop del render
                // (cliente) asi q seria eficiente q ambos tengan la misma solucion
                // (no necesariamente el mismo codigo por q tal vez es muy dificil)
		usleep(MILI2MICRO(1 / UPDATE_FREQ));
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