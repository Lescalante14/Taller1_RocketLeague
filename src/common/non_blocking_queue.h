#ifndef NON_BLOCKING_QUEUE_H
#define NON_BLOCKING_QUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include "queue_empty_exception.h"
#include "queue_closed_exception.h"

template<typename T> class NonBlockingQueue {
    private:
    std::queue<T> internal;
    std::mutex mutex;
    bool is_closed;

    public:
    void push(T &element) {
        std::unique_lock<std::mutex> lock(mutex);
        internal.push(element);
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        if (internal.empty()) {
            throw QueueEmptyException();
        }
        if (is_closed) {
            throw QueueClosedException();
        }
        T element = internal.front();
        internal.pop();
        return element;
    }

    void close() {
        std::unique_lock<std::mutex> lock(mutex);
        is_closed = true;
    }
};

#endif
