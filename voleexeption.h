
#ifndef VOLE_EXCEPTION_H
#define VOLE_EXCEPTION_H

#include <stdexcept>
#include <string>

class VoleException : public std::runtime_error {
public:
    explicit VoleException(const std::string& message)
        : std::runtime_error(message) {
    }
};

class InvalidInstructionException : public VoleException {
public:
    explicit InvalidInstructionException(const std::string& message)
        : VoleException(message) {
    }
};

class InvalidAddressException : public VoleException {
public:
    explicit InvalidAddressException(const std::string& message)
        : VoleException(message) {
    }
};

#endif
