#include <iostream>
#include "client.h"

#define ERROR_CODE 1
#define SUCCESS_CODE 0

int main(int argc, char *argv[]) { try {
    const char *hostname = nullptr;
    const char *servname = nullptr;

    if (argc == 3) {
        hostname = argv[1];
        servname = argv[2];
    } else {
        std::cerr << "Bad program call. Expected "
                << argv[0]
                << " <hostname> <servname>\n";
        return ERROR_CODE;
    }

    Client client;

    client.run(hostname, servname);

    return SUCCESS_CODE;
} catch (const std::exception& err) {
    std::cerr
        << "Something went wrong and an exception was caught: "
        << err.what()
        << "\n";
    return ERROR_CODE;
} catch (...) {
    std::cerr << "Something went wrong and an unknown exception was caught.\n";
    return ERROR_CODE;
} }
