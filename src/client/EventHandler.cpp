//
// Created by lescalante on 20/11/22.
//

#include "EventHandler.h"

#define MAX_ACTIONS 5000

EventHandler::EventHandler(BlockingQueue<std::string> &queue)
:exit_queue(queue) {}

// TODO: add logic to multiple pushActions with limit
bool EventHandler::handleEvents(ClientMatch &match) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN: {
                auto keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_RIGHT:
                        if (!isRightPush) {
                            pushAction(UserAction(RIGHT_PUSH, match.getCarIdAssigned()));
                            isRightPush = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if (!isLeftPush) {
                            pushAction(UserAction(LEFT_PUSH,match.getCarIdAssigned()));
                            isLeftPush = true;
                        }
                        break;
                    case SDLK_UP:
                        if (!isUpPush) {
                            pushAction(UserAction(UP_PUSH,match.getCarIdAssigned()));
                            isUpPush = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (!isDownPush) {
                            pushAction(UserAction(DOWN_PUSH,match.getCarIdAssigned()));
                            isDownPush = true;
                        }
                        break;
                }
                break;
            } // Fin KEY_DOWN
            case SDL_KEYUP: {
                auto keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_RIGHT:
                        pushAction(UserAction(RIGHT_RELEASE,match.getCarIdAssigned()));
                        isRightPush = false;
                        break;
                    case SDLK_LEFT:
                        pushAction(UserAction(LEFT_RELEASE,match.getCarIdAssigned()));
                        isLeftPush = false;
                        break;
                    case SDLK_UP:
                        pushAction(UserAction(UP_RELEASE,match.getCarIdAssigned()));
                        isUpPush = false;
                        break;
                    case SDLK_DOWN:
                        pushAction(UserAction(DOWN_RELEASE,match.getCarIdAssigned()));
                        isDownPush = false;
                        break;
					case SDLK_LSHIFT:
		            	pushAction(UserAction(NITRO_PUSH, match.getCarIdAssigned()));
                        break;

					case SDLK_SPACE:
		            	pushAction(UserAction(JUMP, match.getCarIdAssigned()));
                        break;

                    case SDLK_q:
                        std::cout << "Quit :(" << std::endl;
                        return false;
                }
                break;
            }// Fin KEY_UP
            // case SDL_MOUSEBUTTONDOWN: {
            //     auto mouseEvent = (SDL_MouseButtonEvent &) event;
            //     switch (mouseEvent.button) {
            //         case SDL_BUTTON_LEFT:
            //             break;
            //         case SDL_BUTTON_RIGHT:
            //             pushAction(UserAction(JUMP, match.getCarIdAssigned()));
            //             break;
            //     }
            //     break;
            //} // Fin MOUSE_DOWN
            case SDL_MOUSEBUTTONUP: {
                auto mouseEvent = (SDL_MouseButtonEvent &) event;
                switch (mouseEvent.button) {
                    case SDL_BUTTON_LEFT:
                        pushAction(UserAction(NITRO_RELEASE, match.getCarIdAssigned()));
                        break;
                }
                break;
            }// Fin MOUSE_UP
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        } // fin switch(event)
    	break;
	}
    return true;
}

void EventHandler::pushAction(UserAction action) {
    std::string actionStr = action.serialize();
    if (exit_queue.size() < MAX_ACTIONS) {
		exit_queue.push(actionStr);
    	std::cout << unsigned(action.getCode()) << std::endl;
	}
    // std::string popAction = exit_queue.pop();*/
}
