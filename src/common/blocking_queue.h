#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include "queue_closed_exception.h"

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

    void close() {
        std::unique_lock<std::mutex> lock(this->mutex);
        is_closed = true;
        cv.notify_all();
    }
};

#endif
