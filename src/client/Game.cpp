//
// Created by lescalante on 11/11/22.
//

#include "Game.h"
#include "MockProvider.h"
#include "ClientMatchState.h"
#include "ClientMatch.h"
#include <SDL2pp/SDL2pp.hh>

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
                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN);
    // Creo renderer
    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    MockProvider mockProvider;
    const MatchState& matchState = mockProvider.getInitialMatchState(); //Esto me lo va a dar el protocolo luego

    ClientMatchState clientMatchState(matchState);
    ClientMatch match(clientMatchState, renderer); // Primer capa de presentacion

    renderer.Clear();
    match.render(renderer);
    renderer.Present();
    SDL_Delay(3000);


/*        bool running = true;
        // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
        // del update del modelo.
        while (running) {
            running = handleEvents(car);
            // car = multiple pops()
            //update(car, FRAME_RATE);
            render(renderer, car, fieldImg);
            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(FRAME_RATE);
        }*/
}
