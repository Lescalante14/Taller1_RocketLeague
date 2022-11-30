#include <iostream>
#include "server.h"

#define ERROR_CODE 1
#define SUCCESS_CODE 0

int main(int argc, char *argv[]) { try {
    const char *servname = NULL;

    if (argc == 2) {
        servname = argv[1];
    } else {
        std::cerr << "Bad program call. Expected "
                << argv[0]
                << " <servname>\n";
        return ERROR_CODE;
    }

    Server server;

    server.run(servname);

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