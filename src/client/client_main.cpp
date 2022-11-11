#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>

#define CAR_PIC_WIDTH 529
#define CAR_PIC_HEIGHT 165
#define CAR_WIDTH (CAR_PIC_WIDTH/5)
#define CAR_HEIGHT (CAR_PIC_HEIGHT/5)

int main(int argc, char** argv) {
    std::cout << "Hello world" << std::endl;
    try {
        // Inicializo biblioteca de SDL
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        // Creo una ventana dinamica con titulo "Hello world"
        SDL2pp::Window window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        // Usar factory
        SDL2pp::Texture fieldImg(renderer,
                                 SDL2pp::Surface("./assets/Field.png").SetColorKey(true, 0));
        // Usar factory
        SDL2pp::Texture carImg(renderer,
                               SDL2pp::Surface("./assets/CarF1.png").SetColorKey(true, 0));
        //Car car(carImg);
        // Clear screen
        renderer.Clear();

        // Render our image, stretching it to the whole window
        int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center
        renderer.Copy(fieldImg);
        renderer.Copy(carImg,
                      SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                      SDL2pp::Rect(50, renderer.GetOutputHeight()-100, CAR_WIDTH, CAR_HEIGHT),
                      0.0,                // don't rotate
                      SDL2pp::NullOpt,    // rotation center - not needed
                      SDL_FLIP_NONE
        );
        renderer.Copy(carImg,
                      SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                      SDL2pp::Rect(renderer.GetOutputWidth()-50, renderer.GetOutputHeight()-100, CAR_WIDTH, CAR_HEIGHT),
                      0.0,                // don't rotate
                      SDL2pp::NullOpt,    // rotation center - not needed
                      SDL_FLIP_HORIZONTAL
        );
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
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}