#include "invalidrateexception.h"

#include <string>
InvalidRateException::InvalidRateException() {
    class InvalidRateException : public std::exception {
    private:
        int invalidRate;

    public:
        InvalidRateException(int rate) : invalidRate(rate) {}

        const char* what() const noexcept override {
            std::string message = "RATE ";
            message += std::to_string(invalidRate);
            message += " is not a valid number for a review";
            return message.c_str();
        }
    };
}



