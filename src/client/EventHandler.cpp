//
// Created by lescalante on 20/11/22.
//

#include "EventHandler.h"

bool EventHandler::handleEvents(ClientMatch &match) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                auto keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_RIGHT:
                        if (!isRightPush) {
                            pushAction("rightPush");
                            isRightPush = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if (!isLeftPush) {
                            pushAction("LeftPush");
                            isLeftPush = true;
                        }
                        break;
                    case SDLK_UP:
                        if (!isUpPush) {
                            pushAction("UpPush");
                            isUpPush = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (!isDownPush) {
                            pushAction("DownPush");
                            isDownPush = true;
                        }
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                auto keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_RIGHT:
                        pushAction("rightRelease");
                        isRightPush = false;
                        break;
                    case SDLK_LEFT:
                        std::cout << "leftRelease" << std::endl;
                        isLeftPush = false;
                        break;
                    case SDLK_UP:
                        std::cout << "upRelease" << std::endl;
                        isUpPush = false;
                        break;
                    case SDLK_DOWN:
                        std::cout << "downRelease" << std::endl;
                        isDownPush = false;
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

void EventHandler::pushAction(const char *string) {
    std::cout << string << std::endl;
}
