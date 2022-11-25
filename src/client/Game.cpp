//
// Created by lescalante on 11/11/22.
//
#include <SDL2pp/SDL2pp.hh>
#include <csignal>

#include "EventHandler.h"
#include "Game.h"

#include "client/presentation/ClientMatch.h"
#include "client/model/ClientMatchState.h"
#include "client/helpers/MockProvider.h"
#include "common/match_setup.h"

#define FRAME_RATE 25.0f // 120Hz 


Game::Game(NonBlockingQueue<std::string> &input_queue, BlockingQueue<std::string> &exit_queue)
: input_queue(input_queue), exit_queue(exit_queue) {}


/*
Pseudo Loop:
     while() {
         process input()
         push inputs/commands into exit-queue
         pop game states from input-queue
         update model
         render model
    }
*/
void Game::start(std::istream &input) {
    std::cout << "Hello client" << std::endl;
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          800, 600,
                          SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    MockProvider mockProvider;

    std::cout << "Waiting other players..." << std::endl;
    std::string setupStr = input_queue.blocking_pop();
    std::cout << "starting match..." << std::endl;
    auto matchSetup = MatchSetup(setupStr); //Esto me lo va a dar el protocolo luego
    std::string stateStr = input_queue.blocking_pop();
    auto matchState = MatchState(stateStr); //Esto me lo va a dar el protocolo luego

    //MatchSetup matchSetup = mockProvider.getMatchSetup(); //Esto me lo va a dar el protocolo luego
    //MatchState matchState = mockProvider.getInitialMatchState(); //Esto me lo va a dar el protocolo luego

    ClientMatchState clientMatchState(matchState);
    ClientMatch match(clientMatchState, renderer, matchSetup); // Primer capa de presentacion

    match.render(renderer);

    EventHandler eventHandler(exit_queue);
    bool running = true;

    while (running) {
        // state = multiple pops()
        running = eventHandler.handleEvents(match); // push inside

        std::string newState = input_queue.blocking_pop();
        // Update
        MatchState newMatchState(newState);
        ClientMatchState newClientState(newMatchState);
        ClientMatch newMatch(newClientState, renderer, matchSetup);
        
		std::cout << "Ball position x: " << newMatchState.get_ball_position_x();
		std::cout << ", Ball position y: " << newMatchState.get_ball_position_y();
		std::cout << std::endl;

		// render
		newMatch.render(renderer);
        // la cantidad de microsegundos que debo dormir se debe ajustar en función
        // de la cantidad de tiempo que demoró el handleEvents y el render
        // usleep(FRAME_RATE);
    }
}
