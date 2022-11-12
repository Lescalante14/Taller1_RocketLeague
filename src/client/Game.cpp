//
// Created by lescalante on 11/11/22.
//

#include "Game.h"
#include "MockProvider.h"
#include "ClientMatchState.h"
#include "ClientMatch.h"
#include <SDL2pp/SDL2pp.hh>
#define CAR_PIC_WIDTH 971
#define CAR_PIC_HEIGHT 442
#define CAR_WIDTH (CAR_PIC_WIDTH/8)
#define CAR_HEIGHT (CAR_PIC_HEIGHT/8)

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
    //Field field("./assets/field.jpg", renderer);
    // Usar factory
    /*SDL2pp::Texture fieldImg(renderer,
                             SDL2pp::Surface("./assets/field.jpg").SetColorKey(true, 0));*/
    // Usar factory
    /*SDL2pp::Texture carImg(renderer,
                           SDL2pp::Surface("./assets/car.png").SetColorKey(true, 0));*/

    MockProvider mockProvider;
    const MatchState& matchState = mockProvider.getInitialMatchState(); //Esto me lo va a dar el protocolo luego
    //ClientParser parser;
    ClientMatchState clientMatchState(matchState);
    ClientMatch match(clientMatchState, renderer); // Primer capa de presentacion

    /*ClientCar car("./assets/car.png", renderer);
    ClientCar car2("./assets/car.png", renderer);*/
    // Clear screen
    renderer.Clear();

    // Render our image, stretching it to the whole window
    //int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center
    //renderer.Copy(fieldImg);
    //field.render(renderer);
    match.render(renderer);
    /*renderer.Copy(carImg,
                  SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                  SDL2pp::Rect(50, renderer.GetOutputHeight()-100, CAR_WIDTH, CAR_HEIGHT),
                  0.0,                // don't rotate
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_NONE
    );
    renderer.Copy(carImg,
                  SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                  SDL2pp::Rect(renderer.GetOutputWidth()-CAR_WIDTH-50, renderer.GetOutputHeight()-100, CAR_WIDTH, CAR_HEIGHT),
                  0.0,                // don't rotate
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_HORIZONTAL
    );*/
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
            renderer.Copy(carImg,
                          SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                          SDL2pp::Rect(50, 100, CAR_WIDTH, CAR_HEIGHT),
                          0.0,                // don't rotate
                          SDL2pp::NullOpt,    // rotation center - not needed
                          SDL_FLIP_HORIZONTAL
            );
            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
            usleep(FRAME_RATE);
        }*/
}
