
#ifndef PROGRAM_LOAD_EXCEPTION_H
#define PROGRAM_LOAD_EXCEPTION_H

#include "VoleException.h"

class ProgramLoadException : public VoleException {
public:
    explicit ProgramLoadException(const std::string& message)
        : VoleException(message) {
    }
};

#endif
