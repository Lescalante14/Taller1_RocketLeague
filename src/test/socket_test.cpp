#include "socket_test.h"
#include <cstring>

SocketTest::SocketTest(int skt): Socket(skt) {}

int SocketTest::sendall(
            const void *data,
            unsigned int sz,
            bool *was_closed) {
    char* cdata = (char*)data;
    std::string data_sent(cdata, sz);
    this->data.push(data_sent);
    return sz;
}

int SocketTest::recvall(
            void *data,
            unsigned int sz,
            bool *was_closed) {
    std::string data_recv(this->data.front());
    this->data.pop();
    char* cdata = (char*)data;
    memcpy(cdata, &data_recv[0], sz);
    return sz;
}

SocketTest::~SocketTest() {}