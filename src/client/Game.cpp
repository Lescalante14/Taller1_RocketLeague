//
// Created by lescalante on 11/11/22.
//

#include "Game.h"
#include "helpers/MockProvider.h"
#include "model/ClientMatchState.h"
#include "presentation/ClientMatch.h"
#include "EventHandler.h"
#include "../common/match_setup.h"
#include <SDL2pp/SDL2pp.hh>
#include <csignal>

#define FRAME_RATE 1000000.0f/25.0f

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
    //renderer.Get

    MatchSetup matchSetup = mockProvider.getMatchSetup(); //Esto me lo va a dar el protocolo luego
    const MatchState& matchState = mockProvider.getInitialMatchState(); //Esto me lo va a dar el protocolo luego

    ClientMatchState clientMatchState(matchState);
    ClientMatch match(clientMatchState, renderer, std::move(matchSetup)); // Primer capa de presentacion

    match.render(renderer);

    EventHandler eventHandler{};
    bool running = true;

    while (running) {
        running = eventHandler.handleEvents(match); // push inside
        // state = multiple pops()
        //update(state, FRAME_RATE);
        match.render(renderer);
        // la cantidad de segundos que debo dormir se debe ajustar en función
        // de la cantidad de tiempo que demoró el handleEvents y el render
        usleep(FRAME_RATE);
    }
}
