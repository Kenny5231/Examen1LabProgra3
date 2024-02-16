#ifndef INVALIDRATEEXCEPTION_H
#define INVALIDRATEEXCEPTION_H

#include <exception>
#include <string>

class InvalidRateException : public std::exception {
private:
    int invalidRate;

public:
    InvalidRateException(int rate);
    const char* what() const noexcept override;
};

#endif // INVALIDRATEEXCEPTION_H
