#include "thread_match_handler.h"
#include "../common/queue_empty_exception.h"
#include <algorithm>
#include <unistd.h>
#include <iostream>

ThreadMatchHandler::ThreadMatchHandler(
    LobbyMatch& _match
): match(_match) { }


void ThreadMatchHandler::run() {
    NonBlockingQueue<UserAction>& input_queue = *(this->match.get_match_input_queue());

    while (1) {
        try {
            UserAction action = input_queue.pop();
            std::cout << unsigned(action.get_car_id()) << " " << action.is(UP_PUSH) << std::endl;
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