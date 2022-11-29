#include "thread_acceptor.h"
#include "thread_connection_handler.h"
#include <algorithm>
#include <string>
#include <utility>

void ThreadAcceptor::cleanFinishedHandlers() {
    this->handlers.erase(std::remove_if(
        this->handlers.begin(),
        this->handlers.end(),
        [] (Thread* handler) { 
            if (handler->is_finished()) {
                handler->join();
                delete handler;
                return true;
            }
            return false;
        }), this->handlers.end());
}

void ThreadAcceptor::waitForHandlers() {
    std::for_each(
        this->handlers.begin(), 
        this->handlers.end(), 
        [] (Thread* handler) { 
            handler->join();
            delete handler;
            return true;
        });
}

void ThreadAcceptor::run() {
    try {
        while (*(this->keep_accepting)) {
            Socket peer = this->skt->accept();
            ThreadConnectionHandler* handler = 
                new ThreadConnectionHandler(
                    std::move(peer), 
                    this->lobby);
            handler->start();
            this->handlers.push_back(handler);
            this->cleanFinishedHandlers();
        }
        this->waitForHandlers();
    } catch (const std::exception &e) {
        this->waitForHandlers();
        return;
    } catch (...) {
        this->waitForHandlers();
        return;
    }
}

ThreadAcceptor::ThreadAcceptor(
    Socket* socket, 
    Lobby& _lobby, 
    bool* _keep_accepting
) : skt(socket), 
    lobby(_lobby), 
    keep_accepting(_keep_accepting) { }
