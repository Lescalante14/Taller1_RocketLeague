#include "thread_matchs_handler.h"
#include "thread_match_handler.h"
#include <algorithm>

void ThreadMatchsHandler::cleanFinishedHandlers() {
    this->match_handlers.erase(std::remove_if(
        this->match_handlers.begin(),
        this->match_handlers.end(),
        [] (ThreadMatchHandler* handler) { 
            if (handler->is_finished()) {
                handler->join();
                delete handler;
                return true;
            }
            return false;
        }), this->match_handlers.end());
}

void ThreadMatchsHandler::waitForHandlers() {
    std::for_each(
        this->match_handlers.begin(), 
        this->match_handlers.end(), 
        [] (ThreadMatchHandler* handler) { 
            handler->join();
            delete handler;
            return true;
        });
}

ThreadMatchsHandler::ThreadMatchsHandler(
        BlockingQueue<LobbyMatch*>& _matchs_to_start)
        : matchs_to_start(_matchs_to_start) { }

void ThreadMatchsHandler::run() {
    try {
        bool should_continue = true;

        while (should_continue) {
            try {
                LobbyMatch* match = this->matchs_to_start.pop();
                ThreadMatchHandler* handler = 
                    new ThreadMatchHandler(*match);
                handler->start();
                this->match_handlers.push_back(handler);
                this->cleanFinishedHandlers();
                
            } catch(const QueueClosedException& e) {
                should_continue = false;
            }    
        }
        this->waitForHandlers();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        this->waitForHandlers();
        throw;
    } catch (...) {
        std::cout << "danger" << std::endl;
        this->waitForHandlers();
        return;
    }
}