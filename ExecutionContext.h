#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "ExecutionContext.h"
#include <string>

class Instruction {
public:
    virtual ~Instruction() = default;
    virtual void execute(ExecutionContext& context) = 0;
    virtual std::string describe() const = 0;
};

#endif