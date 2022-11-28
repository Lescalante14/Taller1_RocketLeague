#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include "queue_closed_exception.h"

// OK pero yo tambien meteria un metodo try_pop() q sea
// un pop no bloqueante. De esa manera no tendrias q tener una
// clase NonBlockingQueue separada
template<typename T> class BlockingQueue {
    private:
    std::queue<T> internal;
    std::mutex mutex;
    std::condition_variable cv;
    bool is_closed{};

    public:
    void push(T &element) {
        std::unique_lock<std::mutex> lock(this->mutex);
        internal.push(element);
        cv.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(this->mutex);
        while (internal.empty()) {
            if (is_closed) {
                throw QueueClosedException();
            }
            cv.wait(lock);
        }
        T element = internal.front();
        internal.pop();
        return element;
    }

    // Este metodo sacalo. Jamas le pidas el size a una queue
    // por q 99.99% se la veces vas a tener una race condition
    // (De hecho, este metodo *es* una race condition)
	size_t size() {
		return this->internal.size();
	}

    void close() {
        std::unique_lock<std::mutex> lock(this->mutex);
        is_closed = true;
        cv.notify_all();
    }
};

#endif
