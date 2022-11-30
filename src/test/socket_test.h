#ifndef SOCKET_TEST_H
#define SOCKET_TEST_H

#include "../common/socket.h"
#include <queue>
#include <string>

class SocketTest: public Socket {
private:
    std::queue<std::string> data;

public:
    explicit SocketTest(int skt);
    int sendall(
            const void *data,
            unsigned int sz,
            bool *was_closed) override;
    int recvall(
            void *data,
            unsigned int sz,
            bool *was_closed) override;
    ~SocketTest();
};

#endif
