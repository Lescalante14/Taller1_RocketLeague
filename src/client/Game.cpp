//
// Created by lescalante on 11/11/22.
//
#include <SDL2pp/SDL2pp.hh>
#include <csignal>
#include <utility>

#include "EventHandler.h"
#include "Game.h"

#include "client/presentation/ClientMatch.h"
#include "client/model/ClientMatchState.h"
#include "client/helpers/MockProvider.h"
#include "common/match_setup.h"

#define FRAME_RATE 60 // 60Hz -> (1/60)*(1e^6)
#define SEC2MICRO(t) (t) * 1e6

Game::Game(BlockingQueue<std::string> &received_queue, BlockingQueue<std::string> &to_send_queue)
: received_queue(received_queue), to_send_queue(to_send_queue) {}


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
void Game::run() {
    std::cout << "Waiting other players..." << std::endl;
    std::string setupStr = received_queue.pop();
    std::cout << "starting match..." << std::endl;

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          800, 600,
                          SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();

    MatchSetup matchSetup(setupStr);
    std::string stateStr = received_queue.pop();
    MatchState matchState(stateStr);

    //MockProvider mockProvider;
    //MatchSetup matchSetup = mockProvider.getMatchSetup(); //Esto me lo va a dar el protocolo luego
    //MatchState matchState = mockProvider.getInitialMatchState(); //Esto me lo va a dar el protocolo luego

    ClientMatchState clientMatchState(matchState);

    //Principal presentation layer
    ClientMatch match(clientMatchState, renderer, matchSetup);

    match.render(renderer);

    EventHandler eventHandler(to_send_queue);
    bool running = true;
    bool matchFinished = false;
    std::string actualState = stateStr;
    
	while (running && !matchFinished) {
        running = eventHandler.handleEvents(match); // push inside

        // multiple pops()
        std::string newState = popGameState(actualState, &running);
        actualState = newState;

        // Update
        MatchState newMatchState(newState);
        ClientMatchState newClientState(newMatchState);
        match.updateState(newClientState);
        matchFinished = !newMatchState.get_playing();

        // Render
        match.render(renderer);
        usleep(SEC2MICRO(1 / FRAME_RATE));
    }

    if (matchFinished) {
        // Show stats and other stuff
    }
}

std::string Game::popGameState(std::string actualState, bool *running) {
    std::string lastState = std::move(actualState);
    try {
        for (int i = 0; i < 1; ++i) {
            lastState = received_queue.try_pop();
        }
        return lastState;
    } catch (QueueEmptyException &e) {
        return lastState;
    } catch (QueueClosedException &e) {
        std::cout << "Input queue is closed." << std::endl;
        *running = false;
        return lastState;
    }
}
