#include "invalidrateexception.h"

InvalidRateException::InvalidRateException(int rate) : invalidRate(rate) {}

const char* InvalidRateException::what() const noexcept {
    std::string message = "RATE ";
    message += std::to_string(invalidRate);
    message += " is not a valid number for a review";
    return message.c_str();
}

