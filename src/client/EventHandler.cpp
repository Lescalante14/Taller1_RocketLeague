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
                            pushAction(UserAction(RIGHT_PUSH, 1));
                            isRightPush = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if (!isLeftPush) {
                            pushAction(UserAction(LEFT_PUSH, 2));
                            isLeftPush = true;
                        }
                        break;
                    case SDLK_UP:
                        if (!isUpPush) {
                            pushAction(UserAction(UP_PUSH, 3));
                            isUpPush = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (!isDownPush) {
                            pushAction(UserAction(DOWN_PUSH, 4));
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
                        pushAction(UserAction(RIGHT_RELEASE, 1));
                        isRightPush = false;
                        break;
                    case SDLK_LEFT:
                        pushAction(UserAction(LEFT_RELEASE, 2));
                        isLeftPush = false;
                        break;
                    case SDLK_UP:
                        pushAction(UserAction(UP_RELEASE, 3));
                        isUpPush = false;
                        break;
                    case SDLK_DOWN:
                        pushAction(UserAction(DOWN_RELEASE, 4));
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

void EventHandler::pushAction(UserAction action) {
    std::cout << unsigned(action.get_car_id()) << std::endl;
}
