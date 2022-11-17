//
// Created by lescalante on 11/11/22.
//

#include "Game.h"
#include "MockProvider.h"
#include "ClientMatchState.h"
#include "ClientMatch.h"
#include <SDL2pp/SDL2pp.hh>
#include <csignal>

#define FRAME_RATE 1000000.0f/25.0f

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
    // Inicializo biblioteca de SDL
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    // Creo una ventana dinamica con titulo "Hello world"
    SDL2pp::Window window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          800, 600,
                          SDL_WINDOW_RESIZABLE);
    // Creo renderer
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    MockProvider mockProvider;
    const MatchState& matchState = mockProvider.getInitialMatchState(); //Esto me lo va a dar el protocolo luego

    ClientMatchState clientMatchState(matchState);
    ClientMatch match(clientMatchState, renderer); // Primer capa de presentacion

    renderer.Clear();
    match.render(renderer);
    renderer.Present();
    //SDL_Delay(10000);


    bool running = true;
    // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
    // del update del modelo.
    while (running) {
        running = handleEvents(match); // push inside
        // state = multiple pops()
        match.render(renderer);
        //update(car, FRAME_RATE);
        //render(renderer, );
        // la cantidad de segundos que debo dormir se debe ajustar en función
        // de la cantidad de tiempo que demoró el handleEvents y el render
        usleep(FRAME_RATE);
    }
}

// Puede que este metodo sea responsabilidad de ClientMatch por GRASP
bool Game::handleEvents(ClientMatch &match) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                auto keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_RIGHT:
                        if (!match.clientCarHasRightPush()) {
                            match.pushAction("rightPush");
                            match.setRightIsPushed(true);
                        }
                        break;
                    case SDLK_LEFT:
                        std::cout << "leftPush" << std::endl;
                        break;
                    case SDLK_UP:
                        std::cout << "upPush" << std::endl;
                        break;
                    case SDLK_DOWN:
                        std::cout << "downPush" << std::endl;
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                auto keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_RIGHT:
                        match.pushAction("rightRelease");
                        match.setRightIsPushed(false);
                        break;
                    case SDLK_LEFT:
                        std::cout << "leftRelease" << std::endl;
                        break;
                    case SDLK_UP:
                        std::cout << "upRelease" << std::endl;
                        break;
                    case SDLK_DOWN:
                        std::cout << "downRelease" << std::endl;
                        break;
                    case SDLK_q:
                        std::cout << "Quit :(" << std::endl;
                        return false;
                }
            }// Fin KEY_UP
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        } // fin switch(event)
    }
    return true;
}

