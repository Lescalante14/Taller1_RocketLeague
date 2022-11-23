#ifndef TRANSFERABLE_H
#define TRANSFERABLE_H

#include <string>

class Transferable {
public:
    virtual std::string serialize() = 0;
};

#endif
