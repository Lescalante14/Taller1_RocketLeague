#ifndef CUSTOM_ERROR_H
#define CUSTOM_ERROR_H

#include <exception>
#include <string>

class CustomError : public std::exception {
    private:
    std::string msg;

    public:
    explicit CustomError(std::string _msg);

    virtual const char* what() const noexcept;

    virtual ~CustomError();
};
#endif
